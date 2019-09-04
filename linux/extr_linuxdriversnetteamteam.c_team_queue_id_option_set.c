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
typedef  scalar_t__ u16 ;
struct team_port {scalar_t__ queue_id; } ;
struct TYPE_5__ {scalar_t__ u32_val; } ;
struct team_gsetter_ctx {TYPE_2__ data; TYPE_1__* info; } ;
struct team {TYPE_3__* dev; } ;
struct TYPE_6__ {scalar_t__ real_num_tx_queues; } ;
struct TYPE_4__ {struct team_port* port; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  team_queue_override_port_change_queue_id (struct team*,struct team_port*,scalar_t__) ; 

__attribute__((used)) static int team_queue_id_option_set(struct team *team,
				    struct team_gsetter_ctx *ctx)
{
	struct team_port *port = ctx->info->port;
	u16 new_queue_id = ctx->data.u32_val;

	if (port->queue_id == new_queue_id)
		return 0;
	if (new_queue_id >= team->dev->real_num_tx_queues)
		return -EINVAL;
	team_queue_override_port_change_queue_id(team, port, new_queue_id);
	return 0;
}