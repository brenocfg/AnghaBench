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
struct wined3d_string_buffer {int /*<<< orphan*/  buffer; } ;
struct wined3d_gl_info {int dummy; } ;
struct arbfp_blit_type {int fixup; scalar_t__ use_color_key; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  ARBFP_BLIT_PARAM_SIZE ; 
#define  COMPLEX_FIXUP_NV12 131 
#define  COMPLEX_FIXUP_UYVY 130 
#define  COMPLEX_FIXUP_YUY2 129 
#define  COMPLEX_FIXUP_YV12 128 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FRAGMENT_PROGRAM_ARB ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  gen_nv12_read (struct wined3d_string_buffer*,struct arbfp_blit_type const*,char*) ; 
 int /*<<< orphan*/  gen_planar_yuv_read (struct wined3d_string_buffer*,struct arbfp_blit_type const*,char*) ; 
 int /*<<< orphan*/  gen_yv12_read (struct wined3d_string_buffer*,struct arbfp_blit_type const*,char*) ; 
 int /*<<< orphan*/  glBindProgramARB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenProgramsARB (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_arb_compile (struct wined3d_gl_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_buffer_free (struct wined3d_string_buffer*) ; 
 int /*<<< orphan*/  string_buffer_init (struct wined3d_string_buffer*) ; 

__attribute__((used)) static GLuint gen_yuv_shader(const struct wined3d_gl_info *gl_info, const struct arbfp_blit_type *type)
{
    GLuint shader;
    struct wined3d_string_buffer buffer;
    char luminance_component;

    if (type->use_color_key)
        FIXME("Implement YUV color keying.\n");

    /* Shader header */
    if (!string_buffer_init(&buffer))
    {
        ERR("Failed to initialize shader buffer.\n");
        return 0;
    }

    GL_EXTCALL(glGenProgramsARB(1, &shader));
    checkGLcall("GL_EXTCALL(glGenProgramsARB(1, &shader))");
    GL_EXTCALL(glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, shader));
    checkGLcall("glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, shader)");
    if (!shader)
    {
        string_buffer_free(&buffer);
        return 0;
    }

    /* The YUY2 and UYVY formats contain two pixels packed into a 32 bit macropixel,
     * giving effectively 16 bit per pixel. The color consists of a luminance(Y) and
     * two chroma(U and V) values. Each macropixel has two luminance values, one for
     * each single pixel it contains, and one U and one V value shared between both
     * pixels.
     *
     * The data is loaded into an A8L8 texture. With YUY2, the luminance component
     * contains the luminance and alpha the chroma. With UYVY it is vice versa. Thus
     * take the format into account when generating the read swizzles
     *
     * Reading the Y value is straightforward - just sample the texture. The hardware
     * takes care of filtering in the horizontal and vertical direction.
     *
     * Reading the U and V values is harder. We have to avoid filtering horizontally,
     * because that would mix the U and V values of one pixel or two adjacent pixels.
     * Thus floor the texture coordinate and add 0.5 to get an unfiltered read,
     * regardless of the filtering setting. Vertical filtering works automatically
     * though - the U and V values of two rows are mixed nicely.
     *
     * Apart of avoiding filtering issues, the code has to know which value it just
     * read, and where it can find the other one. To determine this, it checks if
     * it sampled an even or odd pixel, and shifts the 2nd read accordingly.
     *
     * Handling horizontal filtering of U and V values requires reading a 2nd pair
     * of pixels, extracting U and V and mixing them. This is not implemented yet.
     *
     * An alternative implementation idea is to load the texture as A8R8G8B8 texture,
     * with width / 2. This way one read gives all 3 values, finding U and V is easy
     * in an unfiltered situation. Finding the luminance on the other hand requires
     * finding out if it is an odd or even pixel. The real drawback of this approach
     * is filtering. This would have to be emulated completely in the shader, reading
     * up two 2 packed pixels in up to 2 rows and interpolating both horizontally and
     * vertically. Beyond that it would require adjustments to the texture handling
     * code to deal with the width scaling
     */
    shader_addline(&buffer, "!!ARBfp1.0\n");
    shader_addline(&buffer, "TEMP luminance;\n");
    shader_addline(&buffer, "TEMP temp;\n");
    shader_addline(&buffer, "TEMP chroma;\n");
    shader_addline(&buffer, "TEMP texcrd;\n");
    shader_addline(&buffer, "TEMP texcrd2;\n");
    shader_addline(&buffer, "PARAM coef = {1.0, 0.5, 2.0, 0.25};\n");
    shader_addline(&buffer, "PARAM yuv_coef = {1.403, 0.344, 0.714, 1.770};\n");
    shader_addline(&buffer, "PARAM size = program.local[%u];\n", ARBFP_BLIT_PARAM_SIZE);

    switch (type->fixup)
    {
        case COMPLEX_FIXUP_UYVY:
        case COMPLEX_FIXUP_YUY2:
            if (!gen_planar_yuv_read(&buffer, type, &luminance_component))
            {
                string_buffer_free(&buffer);
                return 0;
            }
            break;

        case COMPLEX_FIXUP_YV12:
            if (!gen_yv12_read(&buffer, type, &luminance_component))
            {
                string_buffer_free(&buffer);
                return 0;
            }
            break;

        case COMPLEX_FIXUP_NV12:
            if (!gen_nv12_read(&buffer, type, &luminance_component))
            {
                string_buffer_free(&buffer);
                return 0;
            }
            break;

        default:
            FIXME("Unsupported YUV fixup %#x\n", type->fixup);
            string_buffer_free(&buffer);
            return 0;
    }

    /* Calculate the final result. Formula is taken from
     * http://www.fourcc.org/fccyvrgb.php. Note that the chroma
     * ranges from -0.5 to 0.5
     */
    shader_addline(&buffer, "SUB chroma.xy, chroma, coef.y;\n");

    shader_addline(&buffer, "MAD result.color.x, chroma.x, yuv_coef.x, luminance.%c;\n", luminance_component);
    shader_addline(&buffer, "MAD temp.x, -chroma.y, yuv_coef.y, luminance.%c;\n", luminance_component);
    shader_addline(&buffer, "MAD result.color.y, -chroma.x, yuv_coef.z, temp.x;\n");
    shader_addline(&buffer, "MAD result.color.z, chroma.y, yuv_coef.w, luminance.%c;\n", luminance_component);
    shader_addline(&buffer, "END\n");

    shader_arb_compile(gl_info, GL_FRAGMENT_PROGRAM_ARB, buffer.buffer);

    string_buffer_free(&buffer);

    return shader;
}