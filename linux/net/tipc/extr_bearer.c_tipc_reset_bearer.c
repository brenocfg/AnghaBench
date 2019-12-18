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
struct tipc_bearer {int /*<<< orphan*/  identity; int /*<<< orphan*/  name; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_disc_reset (struct net*,struct tipc_bearer*) ; 
 int /*<<< orphan*/  tipc_node_delete_links (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tipc_reset_bearer(struct net *net, struct tipc_bearer *b)
{
	pr_info("Resetting bearer <%s>\n", b->name);
	tipc_node_delete_links(net, b->identity);
	tipc_disc_reset(net, b);
	return 0;
}