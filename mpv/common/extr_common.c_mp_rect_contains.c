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
struct mp_rect {int x0; int x1; int y0; int y1; } ;

/* Variables and functions */

bool mp_rect_contains(struct mp_rect *rc, int x, int y)
{
    return rc->x0 <= x && x < rc->x1 && rc->y0 <= y && y < rc->y1;
}