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
typedef  unsigned int UINT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */

__attribute__((used)) static void convert_r5g5_snorm_l6_unorm(const BYTE *src, BYTE *dst, UINT src_row_pitch, UINT src_slice_pitch,
        UINT dst_row_pitch, UINT dst_slice_pitch, UINT width, UINT height, UINT depth)
{
    unsigned int x, y, z;
    unsigned char r_in, g_in, l_in;
    const unsigned short *texel_in;
    unsigned short *texel_out;

    /* Emulating signed 5 bit values with unsigned 5 bit values has some precision problems by design:
     * E.g. the signed input value 0 becomes 16. GL normalizes it to 16 / 31 = 0.516. We convert it
     * back to a signed value by subtracting 0.5 and multiplying by 2.0. The resulting value is
     * ((16 / 31) - 0.5) * 2.0 = 0.032, which is quite different from the intended result 0.000. */
    for (z = 0; z < depth; z++)
    {
        for (y = 0; y < height; y++)
        {
            texel_out = (unsigned short *) (dst + z * dst_slice_pitch + y * dst_row_pitch);
            texel_in = (const unsigned short *)(src + z * src_slice_pitch + y * src_row_pitch);
            for (x = 0; x < width; x++ )
            {
                l_in = (*texel_in & 0xfc00u) >> 10;
                g_in = (*texel_in & 0x03e0u) >> 5;
                r_in = *texel_in & 0x001fu;

                *texel_out = ((r_in + 16) << 11) | (l_in << 5) | (g_in + 16);
                texel_out++;
                texel_in++;
            }
        }
    }
}