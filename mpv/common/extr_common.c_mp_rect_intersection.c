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
struct mp_rect {scalar_t__ x0; scalar_t__ y0; scalar_t__ x1; scalar_t__ y1; } ;

/* Variables and functions */
 void* MPMAX (scalar_t__,scalar_t__) ; 
 void* MPMIN (scalar_t__,scalar_t__) ; 

bool mp_rect_intersection(struct mp_rect *rc, const struct mp_rect *rc2)
{
    rc->x0 = MPMAX(rc->x0, rc2->x0);
    rc->y0 = MPMAX(rc->y0, rc2->y0);
    rc->x1 = MPMIN(rc->x1, rc2->x1);
    rc->y1 = MPMIN(rc->y1, rc2->y1);

    return rc->x1 > rc->x0 && rc->y1 > rc->y0;
}