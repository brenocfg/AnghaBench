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
typedef  unsigned char BYTE ;

/* Variables and functions */

__attribute__((used)) static void convert_r5g5_snorm_l6_unorm_ext(const BYTE *src, BYTE *dst, UINT src_row_pitch, UINT src_slice_pitch,
        UINT dst_row_pitch, UINT dst_slice_pitch, UINT width, UINT height, UINT depth)
{
    unsigned int x, y, z;
    unsigned char *texel_out, r_out, g_out, r_in, g_in, l_in;
    const unsigned short *texel_in;

    for (z = 0; z < depth; z++)
    {
        for (y = 0; y < height; y++)
        {
            texel_in = (const unsigned short *)(src + z * src_slice_pitch + y * src_row_pitch);
            texel_out = dst + z * dst_slice_pitch + y * dst_row_pitch;
            for (x = 0; x < width; x++ )
            {
                l_in = (*texel_in & 0xfc00u) >> 10;
                g_in = (*texel_in & 0x03e0u) >> 5;
                r_in = *texel_in & 0x001fu;

                r_out = r_in << 3;
                if (!(r_in & 0x10)) /* r > 0 */
                    r_out |= r_in >> 1;

                g_out = g_in << 3;
                if (!(g_in & 0x10)) /* g > 0 */
                    g_out |= g_in >> 1;

                texel_out[0] = r_out;
                texel_out[1] = g_out;
                texel_out[2] = l_in << 1 | l_in >> 5;
                texel_out[3] = 0;

                texel_out += 4;
                texel_in++;
            }
        }
    }
}