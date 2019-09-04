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
struct device_node {int dummy; } ;

/* Variables and functions */
 int MPC52xx_PSC_MAXNUM ; 
 struct device_node** mpc52xx_uart_nodes ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 

__attribute__((used)) static void
mpc52xx_uart_of_assign(struct device_node *np)
{
	int i;

	/* Find the first free PSC number */
	for (i = 0; i < MPC52xx_PSC_MAXNUM; i++) {
		if (mpc52xx_uart_nodes[i] == NULL) {
			of_node_get(np);
			mpc52xx_uart_nodes[i] = np;
			return;
		}
	}
}