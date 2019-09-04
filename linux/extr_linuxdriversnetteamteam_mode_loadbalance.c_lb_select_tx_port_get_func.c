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
struct lb_select_tx_port {int /*<<< orphan*/ * func; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  lb_select_tx_port_func_t ;

/* Variables and functions */
 int LB_SELECT_TX_PORT_LIST_COUNT ; 
 struct lb_select_tx_port* lb_select_tx_port_list ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static lb_select_tx_port_func_t *lb_select_tx_port_get_func(const char *name)
{
	int i;

	for (i = 0; i < LB_SELECT_TX_PORT_LIST_COUNT; i++) {
		const struct lb_select_tx_port *item;

		item = &lb_select_tx_port_list[i];
		if (!strcmp(item->name, name))
			return item->func;
	}
	return NULL;
}