#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct osd_style_opts {int /*<<< orphan*/  font_size; } ;
struct osd_state {struct mp_osd_render_opts* opts; } ;
struct TYPE_7__ {TYPE_1__* track; } ;
struct TYPE_6__ {double h; } ;
struct osd_object {TYPE_3__ ass; TYPE_2__ vo_res; } ;
struct mp_osd_render_opts {int /*<<< orphan*/  osd_scale_by_window; int /*<<< orphan*/  osd_scale; struct osd_style_opts* osd_style; } ;
struct TYPE_5__ {double PlayResY; } ;
typedef  int /*<<< orphan*/  ASS_Style ;

/* Variables and functions */
 int /*<<< orphan*/  create_ass_track (struct osd_state*,struct osd_object*,TYPE_3__*) ; 
 int /*<<< orphan*/ * get_style (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  mp_ass_set_style (int /*<<< orphan*/ *,double,struct osd_style_opts*) ; 

__attribute__((used)) static ASS_Style *prepare_osd_ass(struct osd_state *osd, struct osd_object *obj)
{
    struct mp_osd_render_opts *opts = osd->opts;

    create_ass_track(osd, obj, &obj->ass);

    struct osd_style_opts font = *opts->osd_style;
    font.font_size *= opts->osd_scale;

    double playresy = obj->ass.track->PlayResY;
    // Compensate for libass and mp_ass_set_style scaling the font etc.
    if (!opts->osd_scale_by_window)
        playresy *= 720.0 / obj->vo_res.h;

    ASS_Style *style = get_style(&obj->ass, "OSD");
    mp_ass_set_style(style, playresy, &font);
    return style;
}