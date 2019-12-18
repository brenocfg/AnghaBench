#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct osd_state {struct mp_osd_render_opts* opts; } ;
struct TYPE_9__ {TYPE_1__* track; } ;
struct osd_object {TYPE_5__ ass; } ;
struct mp_osd_render_opts {double osd_bar_w; double osd_bar_h; int /*<<< orphan*/  osd_bar_align_y; int /*<<< orphan*/  osd_bar_align_x; int /*<<< orphan*/  osd_style; } ;
struct TYPE_8__ {float Outline; int Alignment; scalar_t__ Shadow; } ;
struct TYPE_7__ {double PlayResY; double PlayResX; } ;
typedef  TYPE_1__ ASS_Track ;
typedef  TYPE_2__ ASS_Style ;

/* Variables and functions */
 float MPMAX (float,float) ; 
 float MPMIN (float,float) ; 
 int /*<<< orphan*/  create_ass_track (struct osd_state*,struct osd_object*,TYPE_5__*) ; 
 float get_align (int /*<<< orphan*/ ,double,float,float) ; 
 TYPE_2__* get_style (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  mp_ass_set_style (TYPE_2__*,double,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_osd_bar_box(struct osd_state *osd, struct osd_object *obj,
                            float *o_x, float *o_y, float *o_w, float *o_h,
                            float *o_border)
{
    struct mp_osd_render_opts *opts = osd->opts;

    create_ass_track(osd, obj, &obj->ass);
    ASS_Track *track = obj->ass.track;

    ASS_Style *style = get_style(&obj->ass, "progbar");
    if (!style) {
        *o_x = *o_y = *o_w = *o_h = *o_border = 0;
        return;
    }

    mp_ass_set_style(style, track->PlayResY, opts->osd_style);

    *o_w = track->PlayResX * (opts->osd_bar_w / 100.0);
    *o_h = track->PlayResY * (opts->osd_bar_h / 100.0);

    float base_size = 0.03125;
    style->Outline *= *o_h / track->PlayResY / base_size;
    // So that the chapter marks have space between them
    style->Outline = MPMIN(style->Outline, *o_h / 5.2);
    // So that the border is not 0
    style->Outline = MPMAX(style->Outline, *o_h / 32.0);
    // Rendering with shadow is broken (because there's more than one shape)
    style->Shadow = 0;

    style->Alignment = 5;

    *o_border = style->Outline;

    *o_x = get_align(opts->osd_bar_align_x, track->PlayResX, *o_w, *o_border);
    *o_y = get_align(opts->osd_bar_align_y, track->PlayResY, *o_h, *o_border);
}