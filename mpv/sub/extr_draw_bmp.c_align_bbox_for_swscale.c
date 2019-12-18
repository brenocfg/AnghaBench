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
struct mp_rect {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct mp_image {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;

/* Variables and functions */
 int /*<<< orphan*/  align_bbox (int,int,struct mp_rect*) ; 
 int /*<<< orphan*/  get_swscale_alignment (struct mp_image*,int*,int*) ; 
 int mp_rect_intersection (struct mp_rect*,struct mp_rect*) ; 

__attribute__((used)) static bool align_bbox_for_swscale(struct mp_image *img, struct mp_rect *rc)
{
    struct mp_rect img_rect = {0, 0, img->w, img->h};
    // Get rid of negative coordinates
    if (!mp_rect_intersection(rc, &img_rect))
        return false;
    int xstep, ystep;
    get_swscale_alignment(img, &xstep, &ystep);
    align_bbox(xstep, ystep, rc);
    return mp_rect_intersection(rc, &img_rect);
}