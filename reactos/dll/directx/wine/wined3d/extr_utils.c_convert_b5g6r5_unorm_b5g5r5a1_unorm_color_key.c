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
typedef  int WORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  color_in_range (struct wined3d_color_key const*,int) ; 

__attribute__((used)) static void convert_b5g6r5_unorm_b5g5r5a1_unorm_color_key(const BYTE *src, unsigned int src_pitch,
        BYTE *dst, unsigned int dst_pitch, unsigned int width, unsigned int height,
        const struct wined3d_palette *palette, const struct wined3d_color_key *color_key)
{
    const WORD *src_row;
    unsigned int x, y;
    WORD *dst_row;

    for (y = 0; y < height; ++y)
    {
        src_row = (WORD *)&src[src_pitch * y];
        dst_row = (WORD *)&dst[dst_pitch * y];
        for (x = 0; x < width; ++x)
        {
            WORD src_color = src_row[x];
            if (!color_in_range(color_key, src_color))
                dst_row[x] = 0x8000u | ((src_color & 0xffc0u) >> 1) | (src_color & 0x1fu);
            else
                dst_row[x] = ((src_color & 0xffc0u) >> 1) | (src_color & 0x1fu);
        }
    }
}