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
struct wined3d_palette {int dummy; } ;
struct wined3d_color_key {int dummy; } ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  color_in_range (struct wined3d_color_key const*,int) ; 

__attribute__((used)) static void convert_b8g8r8_unorm_b8g8r8a8_unorm_color_key(const BYTE *src, unsigned int src_pitch,
        BYTE *dst, unsigned int dst_pitch, unsigned int width, unsigned int height,
        const struct wined3d_palette *palette, const struct wined3d_color_key *color_key)
{
    const BYTE *src_row;
    unsigned int x, y;
    DWORD *dst_row;

    for (y = 0; y < height; ++y)
    {
        src_row = &src[src_pitch * y];
        dst_row = (DWORD *)&dst[dst_pitch * y];
        for (x = 0; x < width; ++x)
        {
            DWORD src_color = (src_row[x * 3 + 2] << 16) | (src_row[x * 3 + 1] << 8) | src_row[x * 3];
            if (!color_in_range(color_key, src_color))
                dst_row[x] = src_color | 0xff000000;
        }
    }
}