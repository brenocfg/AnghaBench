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
typedef  int WORD ;
typedef  unsigned int UINT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */

__attribute__((used)) static void convert_s1_uint_d15_unorm(const BYTE *src, BYTE *dst, UINT src_row_pitch, UINT src_slice_pitch,
        UINT dst_row_pitch, UINT dst_slice_pitch, UINT width, UINT height, UINT depth)
{
    unsigned int x, y, z;

    for (z = 0; z < depth; z++)
    {
        for (y = 0; y < height; ++y)
        {
            const WORD *source = (const WORD *)(src + z * src_slice_pitch + y * src_row_pitch);
            DWORD *dest = (DWORD *)(dst + z * dst_slice_pitch + y * dst_row_pitch);

            for (x = 0; x < width; ++x)
            {
                /* The depth data is normalized, so needs to be scaled,
                * the stencil data isn't.  Scale depth data by
                *      (2^24-1)/(2^15-1) ~~ (2^9 + 2^-6). */
                WORD d15 = source[x] >> 1;
                DWORD d24 = (d15 << 9) + (d15 >> 6);
                dest[x] = (d24 << 8) | (source[x] & 0x1);
            }
        }
    }
}