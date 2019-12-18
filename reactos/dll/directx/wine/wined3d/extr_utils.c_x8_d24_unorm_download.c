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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */

__attribute__((used)) static void x8_d24_unorm_download(const BYTE *src, BYTE *dst,
        unsigned int src_row_pitch, unsigned int src_slice_pitch,
        unsigned int dst_row_pitch, unsigned int dst_slice_pitch,
        unsigned int width, unsigned int height, unsigned int depth)
{
    unsigned int x, y, z;

    for (z = 0; z < depth; ++z)
    {
        for (y = 0; y < height; ++y)
        {
            const DWORD *source = (const DWORD *)(src + z * src_slice_pitch + y * src_row_pitch);
            DWORD *dest = (DWORD *)(dst + z * dst_slice_pitch + y * dst_row_pitch);

            for (x = 0; x < width; ++x)
            {
                dest[x] = source[x] >> 8;
            }
        }
    }
}