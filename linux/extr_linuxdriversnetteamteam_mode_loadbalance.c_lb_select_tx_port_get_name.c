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
struct lb_select_tx_port {char* name; int /*<<< orphan*/ * func; } ;
typedef  int /*<<< orphan*/  lb_select_tx_port_func_t ;

/* Variables and functions */
 int LB_SELECT_TX_PORT_LIST_COUNT ; 
 struct lb_select_tx_port* lb_select_tx_port_list ; 

__attribute__((used)) static char *lb_select_tx_port_get_name(lb_select_tx_port_func_t *func)
{
	int i;

	for (i = 0; i < LB_SELECT_TX_PORT_LIST_COUNT; i++) {
		const struct lb_select_tx_port *item;

		item = &lb_select_tx_port_list[i];
		if (item->func == func)
			return item->name;
	}
	return NULL;
}