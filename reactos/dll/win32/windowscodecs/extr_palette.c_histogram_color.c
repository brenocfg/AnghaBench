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
struct histogram {unsigned int*** data; } ;

/* Variables and functions */
 int B_SHIFT ; 
 int G_SHIFT ; 
 int R_SHIFT ; 

__attribute__((used)) static unsigned int histogram_color(struct histogram *h, int r_min, int r_max,
                                    int g_min, int g_max, int b_min, int b_max)
{
    unsigned long long r_sum = 0, g_sum = 0, b_sum = 0;
    unsigned int tmp, count = 0;
    int r, g, b;

    for (r = r_min; r <= r_max; r++)
    for (g = g_min; g <= g_max; g++)
    for (b = b_min; b <= b_max; b++)
    {
        if (!(tmp = h->data[r][g][b])) continue;
        r_sum += ((r << R_SHIFT) + ((1 << R_SHIFT) / 2)) * tmp;
        g_sum += ((g << G_SHIFT) + ((1 << G_SHIFT) / 2)) * tmp;
        b_sum += ((b << B_SHIFT) + ((1 << B_SHIFT) / 2)) * tmp;
        count += tmp;
    }

    return ((b_sum + (count / 2)) / count) |
           ((g_sum + (count / 2)) / count) << 8 |
           ((r_sum + (count / 2)) / count) << 16 | 0xff000000;
}