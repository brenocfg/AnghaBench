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
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rhash_table; } ;
struct ila_net {TYPE_1__ xlat; } ;

/* Variables and functions */
 int alloc_ila_locks (struct ila_net*) ; 
 int /*<<< orphan*/  ila_net_id ; 
 struct ila_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rht_params ; 

int ila_xlat_init_net(struct net *net)
{
	struct ila_net *ilan = net_generic(net, ila_net_id);
	int err;

	err = alloc_ila_locks(ilan);
	if (err)
		return err;

	rhashtable_init(&ilan->xlat.rhash_table, &rht_params);

	return 0;
}