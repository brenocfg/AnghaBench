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
struct TYPE_6__ {int /*<<< orphan*/  linkup_enabled; } ;
struct team_port {TYPE_3__ user; } ;
struct TYPE_5__ {int /*<<< orphan*/  bool_val; } ;
struct team_gsetter_ctx {TYPE_2__ data; TYPE_1__* info; } ;
struct team {int dummy; } ;
struct TYPE_4__ {struct team_port* port; } ;

/* Variables and functions */

__attribute__((used)) static int team_user_linkup_en_option_get(struct team *team,
					  struct team_gsetter_ctx *ctx)
{
	struct team_port *port = ctx->info->port;

	ctx->data.bool_val = port->user.linkup_enabled;
	return 0;
}