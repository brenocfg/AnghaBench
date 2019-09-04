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
struct ra_ctx {TYPE_1__* vo; struct priv* priv; } ;
struct priv {int sc_width; int sc_height; } ;
struct TYPE_2__ {int dwidth; int dheight; } ;

/* Variables and functions */

__attribute__((used)) static void update_sizes(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    p->sc_width = ctx->vo->dwidth ? ctx->vo->dwidth : 1;
    p->sc_height = ctx->vo->dheight ? ctx->vo->dheight : 1;
}