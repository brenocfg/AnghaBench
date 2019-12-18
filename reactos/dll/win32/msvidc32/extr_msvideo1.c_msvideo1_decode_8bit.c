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

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STREAM_PTR (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

__attribute__((used)) static void 
msvideo1_decode_8bit( int width, int height, const unsigned char *buf, int buf_size,
                      unsigned char *pixels, int stride)
{
    int block_ptr, pixel_ptr;
    int total_blocks;
    int pixel_x, pixel_y;  /* pixel width and height iterators */
    int block_x, block_y;  /* block width and height iterators */
    int blocks_wide, blocks_high;  /* width and height in 4x4 blocks */
    int block_inc;
    int row_dec;

    /* decoding parameters */
    int stream_ptr;
    unsigned char byte_a, byte_b;
    unsigned short flags;
    int skip_blocks;
    unsigned char colors[8];

    stream_ptr = 0;
    skip_blocks = 0;
    blocks_wide = width / 4;
    blocks_high = height / 4;
    total_blocks = blocks_wide * blocks_high;
    block_inc = 4;
#ifdef ORIGINAL
    row_dec = stride + 4;
#else
    row_dec = - (stride - 4); /* such that -row_dec > 0 */
#endif

    for (block_y = blocks_high; block_y > 0; block_y--) {
#ifdef ORIGINAL
        block_ptr = ((block_y * 4) - 1) * stride;
#else
        block_ptr = ((blocks_high - block_y) * 4) * stride;
#endif
        for (block_x = blocks_wide; block_x > 0; block_x--) {
            /* check if this block should be skipped */
            if (skip_blocks) {
                block_ptr += block_inc;
                skip_blocks--;
                total_blocks--;
                continue;
            }

            pixel_ptr = block_ptr;

            /* get the next two bytes in the encoded data stream */
            CHECK_STREAM_PTR(2);
            byte_a = buf[stream_ptr++];
            byte_b = buf[stream_ptr++];

            /* check if the decode is finished */
            if ((byte_a == 0) && (byte_b == 0) && (total_blocks == 0))
                return;
            else if ((byte_b & 0xFC) == 0x84) {
                /* skip code, but don't count the current block */
                skip_blocks = ((byte_b - 0x84) << 8) + byte_a - 1;
            } else if (byte_b < 0x80) {
                /* 2-color encoding */
                flags = (byte_b << 8) | byte_a;

                CHECK_STREAM_PTR(2);
                colors[0] = buf[stream_ptr++];
                colors[1] = buf[stream_ptr++];

                for (pixel_y = 0; pixel_y < 4; pixel_y++) {
                    for (pixel_x = 0; pixel_x < 4; pixel_x++, flags >>= 1)
                        pixels[pixel_ptr++] = colors[(flags & 0x1) ^ 1];
                    pixel_ptr -= row_dec;
                }
            } else if (byte_b >= 0x90) {
                /* 8-color encoding */
                flags = (byte_b << 8) | byte_a;

                CHECK_STREAM_PTR(8);
                memcpy(colors, &buf[stream_ptr], 8);
                stream_ptr += 8;

                for (pixel_y = 0; pixel_y < 4; pixel_y++) {
                    for (pixel_x = 0; pixel_x < 4; pixel_x++, flags >>= 1)
                        pixels[pixel_ptr++] =
                            colors[((pixel_y & 0x2) << 1) +
                                (pixel_x & 0x2) + ((flags & 0x1) ^ 1)];
                    pixel_ptr -= row_dec;
                }
            } else {
                /* 1-color encoding */
                colors[0] = byte_a;

                for (pixel_y = 0; pixel_y < 4; pixel_y++) {
                    for (pixel_x = 0; pixel_x < 4; pixel_x++)
                        pixels[pixel_ptr++] = colors[0];
                    pixel_ptr -= row_dec;
                }
            }

            block_ptr += block_inc;
            total_blocks--;
        }
    }
}