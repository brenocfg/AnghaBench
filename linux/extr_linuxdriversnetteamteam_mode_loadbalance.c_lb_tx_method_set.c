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
struct TYPE_2__ {int /*<<< orphan*/  str_val; } ;
struct team_gsetter_ctx {TYPE_1__ data; } ;
struct team {int dummy; } ;
struct lb_priv {int /*<<< orphan*/  select_tx_port_func; } ;
typedef  int /*<<< orphan*/  lb_select_tx_port_func_t ;

/* Variables and functions */
 int EINVAL ; 
 struct lb_priv* get_lb_priv (struct team*) ; 
 int /*<<< orphan*/ * lb_select_tx_port_get_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lb_tx_method_set(struct team *team, struct team_gsetter_ctx *ctx)
{
	struct lb_priv *lb_priv = get_lb_priv(team);
	lb_select_tx_port_func_t *func;

	func = lb_select_tx_port_get_func(ctx->data.str_val);
	if (!func)
		return -EINVAL;
	rcu_assign_pointer(lb_priv->select_tx_port_func, func);
	return 0;
}