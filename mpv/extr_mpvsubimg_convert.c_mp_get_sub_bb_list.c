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
struct sub_bitmaps {int num_parts; struct sub_bitmap* parts; } ;
struct sub_bitmap {scalar_t__ dh; scalar_t__ y; scalar_t__ dw; scalar_t__ x; } ;
struct mp_rect {int x0; int x1; int y0; int y1; scalar_t__ member_3; scalar_t__ member_2; scalar_t__ member_1; scalar_t__ member_0; } ;

/* Variables and functions */
 int MERGE_RC_PIXELS ; 
 int /*<<< orphan*/  mp_rect_union (struct mp_rect*,struct mp_rect*) ; 
 int /*<<< orphan*/  remove_intersecting_rcs (struct mp_rect*,int*) ; 

int mp_get_sub_bb_list(struct sub_bitmaps *sbs, struct mp_rect *out_rc_list,
                       int rc_list_count)
{
    int M = MERGE_RC_PIXELS;
    int num_rc = 0;
    for (int n = 0; n < sbs->num_parts; n++) {
        struct sub_bitmap *sb = &sbs->parts[n];
        struct mp_rect bb = {sb->x, sb->y, sb->x + sb->dw, sb->y + sb->dh};
        bool intersects = false;
        for (int r = 0; r < num_rc; r++) {
            struct mp_rect *rc = &out_rc_list[r];
            if ((bb.x0 - M <= rc->x1 && bb.x1 + M >= rc->x0 &&
                 bb.y0 - M <= rc->y1 && bb.y1 + M >= rc->y0) ||
                num_rc == rc_list_count)
            {
                mp_rect_union(rc, &bb);
                intersects = true;
                break;
            }
        }
        if (!intersects) {
            out_rc_list[num_rc++] = bb;
            remove_intersecting_rcs(out_rc_list, &num_rc);
        }
    }
    remove_intersecting_rcs(out_rc_list, &num_rc);
    return num_rc;
}