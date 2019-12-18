#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mp_image {int dummy; } ;
struct mp_cmd_ctx {int success; TYPE_2__* args; struct MPContext* mpctx; } ;
struct image_writer_opts {int format; } ;
struct MPContext {TYPE_3__* opts; } ;
struct TYPE_6__ {struct image_writer_opts* screenshot_image_opts; } ;
struct TYPE_4__ {char* s; int i; } ;
struct TYPE_5__ {TYPE_1__ v; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGL_ERR ; 
 int image_writer_format_from_ext (char*) ; 
 int image_writer_high_depth (struct image_writer_opts*) ; 
 int /*<<< orphan*/  mp_cmd_msg (struct mp_cmd_ctx*,int /*<<< orphan*/ ,char*) ; 
 char* mp_splitext (char const*,int /*<<< orphan*/ *) ; 
 struct mp_image* screenshot_get (struct MPContext*,int,int) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 
 int write_screenshot (struct mp_cmd_ctx*,struct mp_image*,char const*,struct image_writer_opts*) ; 

void cmd_screenshot_to_file(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;
    const char *filename = cmd->args[0].v.s;
    int mode = cmd->args[1].v.i;
    struct image_writer_opts opts = *mpctx->opts->screenshot_image_opts;

    char *ext = mp_splitext(filename, NULL);
    int format = image_writer_format_from_ext(ext);
    if (format)
        opts.format = format;
    bool high_depth = image_writer_high_depth(&opts);
    struct mp_image *image = screenshot_get(mpctx, mode, high_depth);
    if (!image) {
        mp_cmd_msg(cmd, MSGL_ERR, "Taking screenshot failed.");
        cmd->success = false;
        return;
    }
    cmd->success = write_screenshot(cmd, image, filename, &opts);
    talloc_free(image);
}