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
struct list_head {int dummy; } ;
struct rpc_xprt_switch {int xps_nxprts; struct list_head xps_xprt_list; } ;
struct rpc_xprt_iter {int /*<<< orphan*/ * xpi_cursor; int /*<<< orphan*/  xpi_xpswitch; } ;
struct rpc_xprt {int dummy; } ;

/* Variables and functions */
 struct rpc_xprt_switch* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct rpc_xprt* xprt_switch_find_current_entry (struct list_head*,int /*<<< orphan*/ *) ; 
 struct rpc_xprt* xprt_switch_find_first_entry (struct list_head*) ; 

__attribute__((used)) static
struct rpc_xprt *xprt_iter_current_entry(struct rpc_xprt_iter *xpi)
{
	struct rpc_xprt_switch *xps = rcu_dereference(xpi->xpi_xpswitch);
	struct list_head *head;

	if (xps == NULL)
		return NULL;
	head = &xps->xps_xprt_list;
	if (xpi->xpi_cursor == NULL || xps->xps_nxprts < 2)
		return xprt_switch_find_first_entry(head);
	return xprt_switch_find_current_entry(head, xpi->xpi_cursor);
}