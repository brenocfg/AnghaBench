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
struct image_writer_opts {int dummy; } ;
struct MPContext {int /*<<< orphan*/  log; TYPE_1__* opts; int /*<<< orphan*/ * screenshot_ctx; } ;
typedef  int /*<<< orphan*/  screenshot_ctx ;
struct TYPE_2__ {struct image_writer_opts* screenshot_image_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGL_ERR ; 
 int /*<<< orphan*/  MSGL_INFO ; 
 int /*<<< orphan*/  MSGL_V ; 
 int /*<<< orphan*/  mp_core_lock (struct MPContext*) ; 
 int /*<<< orphan*/  mp_core_unlock (struct MPContext*) ; 
 int /*<<< orphan*/  screenshot_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ write_image (struct mp_image*,struct image_writer_opts*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool write_screenshot(struct MPContext *mpctx, struct mp_image *img,
                             const char *filename, struct image_writer_opts *opts)
{
    screenshot_ctx *ctx = mpctx->screenshot_ctx;
    struct image_writer_opts *gopts = mpctx->opts->screenshot_image_opts;
    struct image_writer_opts opts_copy = opts ? *opts : *gopts;

    screenshot_msg(ctx, MSGL_V, "Starting screenshot: '%s'", filename);

    mp_core_unlock(mpctx);

    bool ok = img && write_image(img, &opts_copy, filename, mpctx->log);

    mp_core_lock(mpctx);

    if (ok) {
        screenshot_msg(ctx, MSGL_INFO, "Screenshot: '%s'", filename);
    } else {
        screenshot_msg(ctx, MSGL_ERR, "Error writing screenshot!");
    }
    return ok;
}