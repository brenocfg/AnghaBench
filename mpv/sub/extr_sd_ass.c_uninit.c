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
struct sd_ass_priv {int /*<<< orphan*/  ass_library; int /*<<< orphan*/  shadow_track; int /*<<< orphan*/  ass_track; scalar_t__ converter; } ;
struct sd {struct sd_ass_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ass_free_track (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ass_library_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_output (struct sd*,int) ; 
 int /*<<< orphan*/  lavc_conv_uninit (scalar_t__) ; 

__attribute__((used)) static void uninit(struct sd *sd)
{
    struct sd_ass_priv *ctx = sd->priv;

    if (ctx->converter)
        lavc_conv_uninit(ctx->converter);
    ass_free_track(ctx->ass_track);
    ass_free_track(ctx->shadow_track);
    enable_output(sd, false);
    ass_library_done(ctx->ass_library);
}