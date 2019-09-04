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
 int MERGE_RC_PIXELS ; 
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (struct mp_rect*,int,int) ; 
 int /*<<< orphan*/  mp_rect_union (struct mp_rect*,struct mp_rect*) ; 

__attribute__((used)) static void remove_intersecting_rcs(struct mp_rect *list, int *count)
{
    int M = MERGE_RC_PIXELS;
    bool changed = true;
    while (changed) {
        changed = false;
        for (int a = 0; a < *count; a++) {
            struct mp_rect *rc_a = &list[a];
            for (int b = *count - 1; b > a; b--) {
                struct mp_rect *rc_b = &list[b];
                if (rc_a->x0 - M <= rc_b->x1 && rc_a->x1 + M >= rc_b->x0 &&
                    rc_a->y0 - M <= rc_b->y1 && rc_a->y1 + M >= rc_b->y0)
                {
                    mp_rect_union(rc_a, rc_b);
                    MP_TARRAY_REMOVE_AT(list, *count, b);
                    changed = true;
                }
            }
        }
    }
}