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
struct mpgl_osd_part {scalar_t__ num_subparts; scalar_t__ prev_num_subparts; } ;
struct mpgl_osd {int stereo_mode; int change_flag; struct mpgl_osd_part** parts; int /*<<< orphan*/  formats; int /*<<< orphan*/  osd_res; int /*<<< orphan*/  osd; } ;
struct mp_osd_res {int dummy; } ;

/* Variables and functions */
 int MAX_OSD_PARTS ; 
 int /*<<< orphan*/  gen_osd_cb ; 
 int /*<<< orphan*/  osd_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mpgl_osd*) ; 
 int /*<<< orphan*/  set_res (struct mpgl_osd*,struct mp_osd_res,int) ; 

void mpgl_osd_generate(struct mpgl_osd *ctx, struct mp_osd_res res, double pts,
                       int stereo_mode, int draw_flags)
{
    for (int n = 0; n < MAX_OSD_PARTS; n++)
        ctx->parts[n]->num_subparts = 0;

    set_res(ctx, res, stereo_mode);

    osd_draw(ctx->osd, ctx->osd_res, pts, draw_flags, ctx->formats, gen_osd_cb, ctx);
    ctx->stereo_mode = stereo_mode;

    // Parts going away does not necessarily result in gen_osd_cb() being called
    // (not even with num_parts==0), so check this separately.
    for (int n = 0; n < MAX_OSD_PARTS; n++) {
        struct mpgl_osd_part *part = ctx->parts[n];
        if (part->num_subparts !=  part->prev_num_subparts)
            ctx->change_flag = true;
        part->prev_num_subparts = part->num_subparts;
    }
}