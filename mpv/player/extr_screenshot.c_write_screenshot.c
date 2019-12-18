#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mp_image {int dummy; } ;
struct mp_cmd_ctx {struct MPContext* mpctx; } ;
struct image_writer_opts {int dummy; } ;
struct MPContext {int /*<<< orphan*/  log; int /*<<< orphan*/  global; TYPE_1__* opts; } ;
struct TYPE_2__ {struct image_writer_opts* screenshot_image_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGL_ERR ; 
 int /*<<< orphan*/  MSGL_INFO ; 
 int /*<<< orphan*/  MSGL_V ; 
 int /*<<< orphan*/  mp_cmd_msg (struct mp_cmd_ctx*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mp_core_lock (struct MPContext*) ; 
 int /*<<< orphan*/  mp_core_unlock (struct MPContext*) ; 
 scalar_t__ write_image (struct mp_image*,struct image_writer_opts*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool write_screenshot(struct mp_cmd_ctx *cmd, struct mp_image *img,
                             const char *filename, struct image_writer_opts *opts)
{
    struct MPContext *mpctx = cmd->mpctx;
    struct image_writer_opts *gopts = mpctx->opts->screenshot_image_opts;
    struct image_writer_opts opts_copy = opts ? *opts : *gopts;

    mp_cmd_msg(cmd, MSGL_V, "Starting screenshot: '%s'", filename);

    mp_core_unlock(mpctx);

    bool ok = img && write_image(img, &opts_copy, filename, mpctx->global,
                                 mpctx->log);

    mp_core_lock(mpctx);

    if (ok) {
        mp_cmd_msg(cmd, MSGL_INFO, "Screenshot: '%s'", filename);
    } else {
        mp_cmd_msg(cmd, MSGL_ERR, "Error writing screenshot!");
    }
    return ok;
}