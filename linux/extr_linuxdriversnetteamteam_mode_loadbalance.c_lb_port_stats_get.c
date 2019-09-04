#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct team_port {int dummy; } ;
struct TYPE_7__ {int len; int /*<<< orphan*/ * ptr; } ;
struct TYPE_8__ {TYPE_3__ bin_val; } ;
struct team_gsetter_ctx {TYPE_4__ data; TYPE_1__* info; } ;
struct team {int dummy; } ;
struct lb_stats {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  stats; } ;
struct lb_port_priv {TYPE_2__ stats_info; } ;
struct TYPE_5__ {struct team_port* port; } ;

/* Variables and functions */
 struct lb_port_priv* get_lb_port_priv (struct team_port*) ; 

__attribute__((used)) static int lb_port_stats_get(struct team *team, struct team_gsetter_ctx *ctx)
{
	struct team_port *port = ctx->info->port;
	struct lb_port_priv *lb_port_priv = get_lb_port_priv(port);

	ctx->data.bin_val.ptr = &lb_port_priv->stats_info.stats;
	ctx->data.bin_val.len = sizeof(struct lb_stats);
	return 0;
}