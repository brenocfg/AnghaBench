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
typedef  int WICColor ;
typedef  size_t UINT ;
typedef  size_t DWORD ;
typedef  size_t BYTE ;

/* Variables and functions */

__attribute__((used)) static UINT rgb_to_palette_index(BYTE r, BYTE g, BYTE b, WICColor *colors, UINT count)
{
    UINT best_diff, best_index, i;

    best_diff = ~0;
    best_index = 0;

    for (i = 0; i < count; i++)
    {
        BYTE pal_r, pal_g, pal_b;
        DWORD diff_r, diff_g, diff_b, diff;

        pal_r = colors[i] >> 16;
        pal_g = colors[i] >> 8;
        pal_b = colors[i];

        diff_r = r - pal_r;
        diff_g = g - pal_g;
        diff_b = b - pal_b;

        diff = diff_r * diff_r + diff_g * diff_g + diff_b * diff_b;
        if (diff == 0) return i;

        if (diff < best_diff)
        {
            best_diff = diff;
            best_index = i;
        }
    }

    return best_index;
}