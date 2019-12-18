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
 int /*<<< orphan*/  vo_wayland_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wayland_vk_wakeup(struct ra_ctx *ctx)
{
    vo_wayland_wakeup(ctx->vo);
}