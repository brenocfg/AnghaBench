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
typedef  unsigned int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 unsigned short float_32_to_16 (float const*) ; 

__attribute__((used)) static void convert_r32_float_r16_float(const BYTE *src, BYTE *dst,
        DWORD pitch_in, DWORD pitch_out, unsigned int w, unsigned int h)
{
    unsigned short *dst_s;
    const float *src_f;
    unsigned int x, y;

    TRACE("Converting %ux%u pixels, pitches %u %u.\n", w, h, pitch_in, pitch_out);

    for (y = 0; y < h; ++y)
    {
        src_f = (const float *)(src + y * pitch_in);
        dst_s = (unsigned short *) (dst + y * pitch_out);
        for (x = 0; x < w; ++x)
        {
            dst_s[x] = float_32_to_16(src_f + x);
        }
    }
}