#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_palette {TYPE_1__* colors; } ;
struct wined3d_color_key {int dummy; } ;
struct TYPE_2__ {int rgbRed; int rgbGreen; int rgbBlue; } ;
typedef  int DWORD ;
typedef  size_t BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void convert_p8_uint_b8g8r8a8_unorm(const BYTE *src, unsigned int src_pitch,
        BYTE *dst, unsigned int dst_pitch, unsigned int width, unsigned int height,
        const struct wined3d_palette *palette, const struct wined3d_color_key *color_key)
{
    const BYTE *src_row;
    unsigned int x, y;
    DWORD *dst_row;

    if (!palette)
    {
        /* FIXME: This should probably use the system palette. */
        FIXME("P8 surface loaded without a palette.\n");

        for (y = 0; y < height; ++y)
        {
            memset(&dst[dst_pitch * y], 0, width * 4);
        }

        return;
    }

    for (y = 0; y < height; ++y)
    {
        src_row = &src[src_pitch * y];
        dst_row = (DWORD *)&dst[dst_pitch * y];
        for (x = 0; x < width; ++x)
        {
            BYTE src_color = src_row[x];
            dst_row[x] = 0xff000000
                    | (palette->colors[src_color].rgbRed << 16)
                    | (palette->colors[src_color].rgbGreen << 8)
                    | palette->colors[src_color].rgbBlue;
        }
    }
}