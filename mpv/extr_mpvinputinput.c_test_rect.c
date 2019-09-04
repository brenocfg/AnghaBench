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
struct mp_rect {int x0; int y0; int x1; int y1; } ;

/* Variables and functions */

__attribute__((used)) static bool test_rect(struct mp_rect *rc, int x, int y)
{
    return x >= rc->x0 && y >= rc->y0 && x < rc->x1 && y < rc->y1;
}