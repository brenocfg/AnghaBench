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
struct sd_ass_priv {scalar_t__ converter; scalar_t__ num_seen_packets; int /*<<< orphan*/  ass_track; scalar_t__ duration_unknown; } ;
struct sd {int preload_ok; TYPE_1__* opts; struct sd_ass_priv* priv; } ;
struct TYPE_2__ {scalar_t__ sub_clear_on_seek; } ;

/* Variables and functions */
 int /*<<< orphan*/  ass_flush_events (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lavc_conv_reset (scalar_t__) ; 

__attribute__((used)) static void reset(struct sd *sd)
{
    struct sd_ass_priv *ctx = sd->priv;
    if (sd->opts->sub_clear_on_seek || ctx->duration_unknown) {
        ass_flush_events(ctx->ass_track);
        ctx->num_seen_packets = 0;
        sd->preload_ok = false;
    }
    if (ctx->converter)
        lavc_conv_reset(ctx->converter);
}