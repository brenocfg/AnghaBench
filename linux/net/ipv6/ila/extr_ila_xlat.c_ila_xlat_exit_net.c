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
struct TYPE_2__ {scalar_t__ hooks_registered; int /*<<< orphan*/  locks; int /*<<< orphan*/  rhash_table; } ;
struct ila_net {TYPE_1__ xlat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_bucket_spinlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ila_free_cb ; 
 int /*<<< orphan*/  ila_net_id ; 
 int /*<<< orphan*/  ila_nf_hook_ops ; 
 struct ila_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_unregister_net_hooks (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_free_and_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ila_xlat_exit_net(struct net *net)
{
	struct ila_net *ilan = net_generic(net, ila_net_id);

	rhashtable_free_and_destroy(&ilan->xlat.rhash_table, ila_free_cb, NULL);

	free_bucket_spinlocks(ilan->xlat.locks);

	if (ilan->xlat.hooks_registered)
		nf_unregister_net_hooks(net, ila_nf_hook_ops,
					ARRAY_SIZE(ila_nf_hook_ops));
}