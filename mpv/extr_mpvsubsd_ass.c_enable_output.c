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
struct sd_ass_priv {int /*<<< orphan*/ * ass_renderer; int /*<<< orphan*/  ass_library; } ;
struct sd {int /*<<< orphan*/  log; int /*<<< orphan*/  global; TYPE_1__* opts; struct sd_ass_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  sub_style; } ;

/* Variables and functions */
 int /*<<< orphan*/  ass_renderer_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ass_renderer_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_ass_configure_fonts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_output(struct sd *sd, bool enable)
{
    struct sd_ass_priv *ctx = sd->priv;
    if (enable == !!ctx->ass_renderer)
        return;
    if (ctx->ass_renderer) {
        ass_renderer_done(ctx->ass_renderer);
        ctx->ass_renderer = NULL;
    } else {
        ctx->ass_renderer = ass_renderer_init(ctx->ass_library);

        mp_ass_configure_fonts(ctx->ass_renderer, sd->opts->sub_style,
                               sd->global, sd->log);
    }
}