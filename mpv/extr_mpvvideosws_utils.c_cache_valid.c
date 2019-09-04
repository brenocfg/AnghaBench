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
struct mp_sws_context {scalar_t__ flags; scalar_t__ brightness; scalar_t__ contrast; scalar_t__ saturation; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; scalar_t__ force_reload; struct mp_sws_context* cached; } ;

/* Variables and functions */
 scalar_t__ mp_image_params_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool cache_valid(struct mp_sws_context *ctx)
{
    struct mp_sws_context *old = ctx->cached;
    if (ctx->force_reload)
        return false;
    return mp_image_params_equal(&ctx->src, &old->src) &&
           mp_image_params_equal(&ctx->dst, &old->dst) &&
           ctx->flags == old->flags &&
           ctx->brightness == old->brightness &&
           ctx->contrast == old->contrast &&
           ctx->saturation == old->saturation;
}