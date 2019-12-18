#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gl_shader_cache {int dummy; } ;
struct error_diffusion_kernel {int shift; int divisor; int** pattern; } ;

/* Variables and functions */
 int EF_MAX_DELTA_X ; 
 int EF_MAX_DELTA_Y ; 
 int EF_MIN_DELTA_X ; 
 int /*<<< orphan*/  GLSL (char*,...) ; 
 int /*<<< orphan*/  GLSLH (char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int compute_rightmost_shifted_column (struct error_diffusion_kernel const*) ; 

void pass_error_diffusion(struct gl_shader_cache *sc,
                          const struct error_diffusion_kernel *k,
                          int tex, int width, int height, int depth, int block_size)
{
    assert(block_size <= height);

    // The parallel error diffusion works by applying the shift mapping first.
    // Taking the Floyd and Steinberg algorithm for example. After applying
    // the (y, x) -> (y, x + y * shift) mapping (with shift=2), all errors are
    // propagated into the next few columns, which makes parallel processing on
    // the same column possible.
    //
    //           X    7/16                X    7/16
    //    3/16  5/16  1/16   ==>    0     0    3/16  5/16  1/16

    // Figuring out the size of rectangle containing all shifted pixels.
    // The rectangle height is not changed.
    int shifted_width = width + (height - 1) * k->shift;

    // We process all pixels from the shifted rectangles column by column, with
    // a single global work group of size |block_size|.
    // Figuring out how many block are required to process all pixels. We need
    // this explicitly to make the number of barrier() calls match.
    int blocks = (height * shifted_width + block_size - 1) / block_size;

    // If we figure out how many of the next columns will be affected while the
    // current columns is being processed. We can store errors of only a few
    // columns in the shared memory. Using a ring buffer will further save the
    // cost while iterating to next column.
    int ring_buffer_rows = height + EF_MAX_DELTA_Y;
    int ring_buffer_columns = compute_rightmost_shifted_column(k) + 1;
    int ring_buffer_size = ring_buffer_rows * ring_buffer_columns;

    // Defines the ring buffer in shared memory.
    GLSLH("shared uint err_rgb8[%d];\n", ring_buffer_size);

    // Initialize the ring buffer.
    GLSL("for (int i = int(gl_LocalInvocationIndex); i < %d; i += %d) ",
         ring_buffer_size, block_size);
    GLSL("err_rgb8[i] = 0;\n");

    GLSL("for (int block_id = 0; block_id < %d; ++block_id) {\n", blocks);

    // Add barrier here to have previous block all processed before starting
    // the processing of the next.
    GLSL("groupMemoryBarrier();\n");
    GLSL("barrier();\n");

    // Compute the coordinate of the pixel we are currently processing, both
    // before and after the shift mapping.
    GLSL("int id = int(gl_LocalInvocationIndex) + block_id * %d;\n", block_size);
    GLSL("int y = id %% %d, x_shifted = id / %d;\n", height, height);
    GLSL("int x = x_shifted - y * %d;\n", k->shift);

    // Proceed only if we are processing a valid pixel.
    GLSL("if (0 <= x && x < %d) {\n", width);

    // The index that the current pixel have on the ring buffer.
    GLSL("int idx = (x_shifted * %d + y) %% %d;\n", ring_buffer_rows, ring_buffer_size);

    // Fetch the current pixel.
    GLSL("vec3 pix = texelFetch(texture%d, ivec2(x, y), 0).rgb;\n", tex);

    // The dithering will quantize pixel value into multiples of 1/dither_quant.
    int dither_quant = (1 << depth) - 1;

    // We encode errors in RGB components into a single 32-bit unsigned integer.
    // The error we propagate from the current pixel is in range of
    // [-0.5 / dither_quant, 0.5 / dither_quant]. While not quite obvious, the
    // sum of all errors been propagated into a pixel is also in the same range.
    // It's possible to map errors in this range into [-127, 127], and use an
    // unsigned 8-bit integer to store it (using standard two's complement).
    // The three 8-bit unsigned integers can then be encoded into a single
    // 32-bit unsigned integer, with two 4-bit padding to prevent addition
    // operation overflows affecting other component. There are at most 12
    // addition operations on each pixel, so 4-bit padding should be enough.
    // The overflow from R component will be discarded.
    //
    // The following figure is how the encoding looks like.
    //
    //     +------------------------------------+
    //     |RRRRRRRR|0000|GGGGGGGG|0000|BBBBBBBB|
    //     +------------------------------------+
    //

    // The bitshift position for R and G component.
    int bitshift_r = 24, bitshift_g = 12;
    // The multiplier we use to map [-0.5, 0.5] to [-127, 127].
    int uint8_mul = 127 * 2;

    // Adding the error previously propagated into current pixel, and clear it
    // in the buffer.
    GLSL("uint err_u32 = err_rgb8[idx] + %uu;\n",
         (128u << bitshift_r) | (128u << bitshift_g) | 128u);
    GLSL("pix = pix * %d.0 + vec3("
         "int((err_u32 >> %d) & 255u) - 128,"
         "int((err_u32 >> %d) & 255u) - 128,"
         "int( err_u32        & 255u) - 128"
         ") / %d.0;\n", dither_quant, bitshift_r, bitshift_g, uint8_mul);
    GLSL("err_rgb8[idx] = 0;\n");

    // Write the dithered pixel.
    GLSL("vec3 dithered = round(pix);\n");
    GLSL("imageStore(out_image, ivec2(x, y), vec4(dithered / %d.0, 0.0));\n",
         dither_quant);

    GLSL("vec3 err_divided = (pix - dithered) * %d.0 / %d.0;\n",
         uint8_mul, k->divisor);
    GLSL("ivec3 tmp;\n");

    // Group error propagation with same weight factor together, in order to
    // reduce the number of annoying error encoding.
    for (int dividend = 1; dividend <= k->divisor; dividend++) {
        bool err_assigned = false;

        for (int y = 0; y <= EF_MAX_DELTA_Y; y++) {
            for (int x = EF_MIN_DELTA_X; x <= EF_MAX_DELTA_X; x++) {
                if (k->pattern[y][x - EF_MIN_DELTA_X] != dividend)
                    continue;

                if (!err_assigned) {
                    err_assigned = true;

                    GLSL("tmp = ivec3(round(err_divided * %d.0));\n", dividend);

                    GLSL("err_u32 = "
                         "(uint(tmp.r & 255) << %d)|"
                         "(uint(tmp.g & 255) << %d)|"
                         " uint(tmp.b & 255);\n",
                         bitshift_r, bitshift_g);
                }

                int shifted_x = x + y * k->shift;

                // Unlike the right border, errors propagated out from left
                // border will remain in the ring buffer. This will produce
                // visible artifacts near the left border, especially for
                // shift=3 kernels.
                if (x < 0)
                    GLSL("if (x >= %d) ", -x);

                // Calculate the new position in the ring buffer to propagate
                // the error into.
                int ring_buffer_delta = shifted_x * ring_buffer_rows + y;
                GLSL("atomicAdd(err_rgb8[(idx + %d) %% %d], err_u32);\n",
                     ring_buffer_delta, ring_buffer_size);
            }
        }
    }

    GLSL("}\n"); // if (0 <= x && x < width)

    GLSL("}\n"); // block_id
}