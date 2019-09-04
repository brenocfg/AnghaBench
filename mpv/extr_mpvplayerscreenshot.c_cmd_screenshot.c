#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  char mp_image ;
struct mp_cmd_ctx {int msg_osd; int success; int /*<<< orphan*/  cmd; TYPE_2__* args; struct MPContext* mpctx; } ;
struct image_writer_opts {int dummy; } ;
struct MPContext {TYPE_5__* opts; int /*<<< orphan*/  osd; TYPE_6__* screenshot_ctx; } ;
struct TYPE_17__ {int osd; TYPE_7__* each_frame; } ;
typedef  TYPE_6__ screenshot_ctx ;
struct TYPE_18__ {TYPE_4__* args; } ;
struct TYPE_16__ {struct image_writer_opts* screenshot_image_opts; } ;
struct TYPE_14__ {int i; } ;
struct TYPE_15__ {TYPE_3__ v; } ;
struct TYPE_12__ {int i; } ;
struct TYPE_13__ {TYPE_1__ v; } ;

/* Variables and functions */
 int MODE_SUBTITLES ; 
 int /*<<< orphan*/  MSGL_ERR ; 
 int /*<<< orphan*/  TA_FREEP (TYPE_7__**) ; 
 char* gen_fname (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  image_writer_file_ext (struct image_writer_opts*) ; 
 int image_writer_high_depth (struct image_writer_opts*) ; 
 int /*<<< orphan*/  mp_cmd_clone (int /*<<< orphan*/ ) ; 
 scalar_t__ osd_get_render_subs_in_filter (int /*<<< orphan*/ ) ; 
 char* screenshot_get (struct MPContext*,int,int) ; 
 int /*<<< orphan*/  screenshot_msg (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 TYPE_7__* talloc_steal (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int write_screenshot (struct MPContext*,char*,char*,int /*<<< orphan*/ *) ; 

void cmd_screenshot(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;
    int mode = cmd->args[0].v.i & 3;
    bool each_frame_toggle = (cmd->args[0].v.i | cmd->args[1].v.i) & 8;
    bool each_frame_mode = cmd->args[0].v.i & 16;
    bool osd = cmd->msg_osd;

    screenshot_ctx *ctx = mpctx->screenshot_ctx;

    if (mode == MODE_SUBTITLES && osd_get_render_subs_in_filter(mpctx->osd))
        mode = 0;

    if (!each_frame_mode) {
        if (each_frame_toggle) {
            if (ctx->each_frame) {
                TA_FREEP(&ctx->each_frame);
                return;
            }
            ctx->each_frame = talloc_steal(ctx, mp_cmd_clone(cmd->cmd));
            ctx->each_frame->args[0].v.i |= 16;
        } else {
            TA_FREEP(&ctx->each_frame);
        }
    }

    cmd->success = false;

    ctx->osd = osd;

    struct image_writer_opts *opts = mpctx->opts->screenshot_image_opts;
    bool high_depth = image_writer_high_depth(opts);

    struct mp_image *image = screenshot_get(mpctx, mode, high_depth);

    if (image) {
        char *filename = gen_fname(ctx, image_writer_file_ext(opts));
        if (filename)
            cmd->success = write_screenshot(mpctx, image, filename, NULL);
        talloc_free(filename);
    } else {
        screenshot_msg(ctx, MSGL_ERR, "Taking screenshot failed.");
    }

    talloc_free(image);
}