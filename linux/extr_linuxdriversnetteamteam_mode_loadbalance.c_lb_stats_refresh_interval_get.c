#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  u32_val; } ;
struct team_gsetter_ctx {TYPE_1__ data; } ;
struct team {int dummy; } ;
struct lb_priv {TYPE_3__* ex; } ;
struct TYPE_5__ {int /*<<< orphan*/  refresh_interval; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;

/* Variables and functions */
 struct lb_priv* get_lb_priv (struct team*) ; 

__attribute__((used)) static int lb_stats_refresh_interval_get(struct team *team,
					 struct team_gsetter_ctx *ctx)
{
	struct lb_priv *lb_priv = get_lb_priv(team);

	ctx->data.u32_val = lb_priv->ex->stats.refresh_interval;
	return 0;
}