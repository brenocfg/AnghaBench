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
struct ra_ctx {int /*<<< orphan*/  vo; } ;

/* Variables and functions */
 int /*<<< orphan*/  resize (struct ra_ctx*) ; 
 int /*<<< orphan*/  vo_x11_config_vo_window (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mpegl_reconfig(struct ra_ctx *ctx)
{
    vo_x11_config_vo_window(ctx->vo);
    resize(ctx);
    return true;
}