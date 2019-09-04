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
struct vo_vsync_info {int /*<<< orphan*/  last_queue_display_time; int /*<<< orphan*/  skipped_vsyncs; int /*<<< orphan*/  vsync_duration; } ;
struct ra_ctx {struct priv* priv; } ;
struct priv {int /*<<< orphan*/  last_queue_display_time; int /*<<< orphan*/  last_skipped_vsyncs; int /*<<< orphan*/  vsync_duration; } ;

/* Variables and functions */

__attribute__((used)) static void glx_get_vsync(struct ra_ctx *ctx, struct vo_vsync_info *info)
{
    struct priv *p = ctx->priv;
    info->vsync_duration = p->vsync_duration;
    info->skipped_vsyncs = p->last_skipped_vsyncs;
    info->last_queue_display_time = p->last_queue_display_time;
}