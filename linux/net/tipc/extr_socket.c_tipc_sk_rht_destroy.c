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
struct tipc_net {int /*<<< orphan*/  sk_rht; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct tipc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 int /*<<< orphan*/  tipc_net_id ; 

void tipc_sk_rht_destroy(struct net *net)
{
	struct tipc_net *tn = net_generic(net, tipc_net_id);

	/* Wait for socket readers to complete */
	synchronize_net();

	rhashtable_destroy(&tn->sk_rht);
}