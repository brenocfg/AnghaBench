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
typedef  unsigned int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  pfetch_2d_texel_rgba_dxt3 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int,unsigned int,unsigned int*) ; 

__attribute__((used)) static inline BOOL dxt3_to_x4r4g4b4(const BYTE *src, BYTE *dst, DWORD pitch_in,
        DWORD pitch_out, unsigned int w, unsigned int h, BOOL alpha)
{
    unsigned int x, y;
    DWORD color;

    TRACE("Converting %ux%u pixels, pitches %u %u\n", w, h, pitch_in, pitch_out);

    for (y = 0; y < h; ++y)
    {
        WORD *dst_line = (WORD *)(dst + y * pitch_out);
        for (x = 0; x < w; ++x)
        {
            /* pfetch_2d_texel_rgba_dxt3 doesn't correctly handle pitch */
            pfetch_2d_texel_rgba_dxt3(0, src + (y / 4) * pitch_in + (x / 4) * 16,
                                      x & 3, y & 3, &color);
            if (alpha)
            {
                dst_line[x] = ((color & 0xf0000000) >> 16) | ((color & 0xf00000) >> 20) |
                              ((color & 0xf000) >> 8) | ((color & 0xf0) << 4);
            }
            else
            {
                dst_line[x] = 0xf000  | ((color & 0xf00000) >> 20) |
                              ((color & 0xf000) >> 8) | ((color & 0xf0) << 4);
            }
        }
    }

    return TRUE;
}