#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vo {int /*<<< orphan*/  osd; int /*<<< orphan*/  params; struct priv* priv; } ;
struct mp_osd_res {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  fourcc; } ;
struct priv {size_t output_surface; TYPE_2__* osd_parts; struct mp_osd_res screen_osd_res; scalar_t__ osd_screen; TYPE_1__ osd_format; struct mp_image** output_surfaces; } ;
struct mp_image {double pts; } ;
struct TYPE_4__ {int active; } ;

/* Variables and functions */
 int MAX_OSD_PARTS ; 
 int /*<<< orphan*/  draw_osd_cb ; 
 int /*<<< orphan*/  osd_draw (int /*<<< orphan*/ ,struct mp_osd_res,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct priv*) ; 
 int /*<<< orphan*/  osd_formats ; 
 struct mp_osd_res osd_res_from_image_params (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_osd(struct vo *vo)
{
    struct priv *p = vo->priv;

    struct mp_image *cur = p->output_surfaces[p->output_surface];
    double pts = cur ? cur->pts : 0;

    if (!p->osd_format.fourcc)
        return;

    struct mp_osd_res vid_res = osd_res_from_image_params(vo->params);

    struct mp_osd_res *res;
    if (p->osd_screen) {
        res = &p->screen_osd_res;
    } else {
        res = &vid_res;
    }

    for (int n = 0; n < MAX_OSD_PARTS; n++)
        p->osd_parts[n].active = false;
    osd_draw(vo->osd, *res, pts, 0, osd_formats, draw_osd_cb, p);
}