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

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void convert_r5g6b5_x8r8g8b8(const BYTE *src, BYTE *dst,
        DWORD pitch_in, DWORD pitch_out, unsigned int w, unsigned int h)
{
    static const unsigned char convert_5to8[] =
    {
        0x00, 0x08, 0x10, 0x19, 0x21, 0x29, 0x31, 0x3a,
        0x42, 0x4a, 0x52, 0x5a, 0x63, 0x6b, 0x73, 0x7b,
        0x84, 0x8c, 0x94, 0x9c, 0xa5, 0xad, 0xb5, 0xbd,
        0xc5, 0xce, 0xd6, 0xde, 0xe6, 0xef, 0xf7, 0xff,
    };
    static const unsigned char convert_6to8[] =
    {
        0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, 0x18, 0x1c,
        0x20, 0x24, 0x28, 0x2d, 0x31, 0x35, 0x39, 0x3d,
        0x41, 0x45, 0x49, 0x4d, 0x51, 0x55, 0x59, 0x5d,
        0x61, 0x65, 0x69, 0x6d, 0x71, 0x75, 0x79, 0x7d,
        0x82, 0x86, 0x8a, 0x8e, 0x92, 0x96, 0x9a, 0x9e,
        0xa2, 0xa6, 0xaa, 0xae, 0xb2, 0xb6, 0xba, 0xbe,
        0xc2, 0xc6, 0xca, 0xce, 0xd2, 0xd7, 0xdb, 0xdf,
        0xe3, 0xe7, 0xeb, 0xef, 0xf3, 0xf7, 0xfb, 0xff,
    };
    unsigned int x, y;

    TRACE("Converting %ux%u pixels, pitches %u %u.\n", w, h, pitch_in, pitch_out);

    for (y = 0; y < h; ++y)
    {
        const WORD *src_line = (const WORD *)(src + y * pitch_in);
        DWORD *dst_line = (DWORD *)(dst + y * pitch_out);
        for (x = 0; x < w; ++x)
        {
            WORD pixel = src_line[x];
            dst_line[x] = 0xff000000u
                    | convert_5to8[(pixel & 0xf800u) >> 11] << 16
                    | convert_6to8[(pixel & 0x07e0u) >> 5] << 8
                    | convert_5to8[(pixel & 0x001fu)];
        }
    }
}