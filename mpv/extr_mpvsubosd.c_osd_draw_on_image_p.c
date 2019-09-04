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
struct osd_state {int dummy; } ;
struct mp_osd_res {int dummy; } ;
struct mp_image_pool {int dummy; } ;
struct mp_image {int dummy; } ;
struct draw_on_image_closure {struct mp_image_pool* member_2; struct mp_image* member_1; struct osd_state* member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  draw_on_image ; 
 int /*<<< orphan*/  mp_draw_sub_formats ; 
 int /*<<< orphan*/  osd_draw (struct osd_state*,struct mp_osd_res,double,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct draw_on_image_closure*) ; 

void osd_draw_on_image_p(struct osd_state *osd, struct mp_osd_res res,
                         double video_pts, int draw_flags,
                         struct mp_image_pool *pool, struct mp_image *dest)
{
    struct draw_on_image_closure closure = {osd, dest, pool};
    osd_draw(osd, res, video_pts, draw_flags, mp_draw_sub_formats,
             &draw_on_image, &closure);
}