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
struct team_port {TYPE_3__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  u32_val; } ;
struct team_gsetter_ctx {TYPE_2__ data; TYPE_1__* info; } ;
struct team {int dummy; } ;
struct lb_priv {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ifindex; } ;
struct TYPE_4__ {unsigned char array_index; } ;

/* Variables and functions */
 struct team_port* LB_HTPM_PORT_BY_HASH (struct lb_priv*,unsigned char) ; 
 struct lb_priv* get_lb_priv (struct team*) ; 

__attribute__((used)) static int lb_tx_hash_to_port_mapping_get(struct team *team,
					  struct team_gsetter_ctx *ctx)
{
	struct lb_priv *lb_priv = get_lb_priv(team);
	struct team_port *port;
	unsigned char hash = ctx->info->array_index;

	port = LB_HTPM_PORT_BY_HASH(lb_priv, hash);
	ctx->data.u32_val = port ? port->dev->ifindex : 0;
	return 0;
}