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
typedef  scalar_t__ u32 ;
struct tipc_nlist {scalar_t__ self; int local; int /*<<< orphan*/  remote; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ tipc_dest_push (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

void tipc_nlist_add(struct tipc_nlist *nl, u32 node)
{
	if (node == nl->self)
		nl->local = true;
	else if (tipc_dest_push(&nl->list, node, 0))
		nl->remote++;
}