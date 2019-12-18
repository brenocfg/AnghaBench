#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpv_render_param ;
struct TYPE_6__ {TYPE_3__* renderer; } ;
typedef  TYPE_2__ mpv_render_context ;
struct TYPE_7__ {TYPE_1__* fns; } ;
struct TYPE_5__ {int (* set_parameter ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

int mpv_render_context_set_parameter(mpv_render_context *ctx,
                                     mpv_render_param param)
{
    return ctx->renderer->fns->set_parameter(ctx->renderer, param);
}