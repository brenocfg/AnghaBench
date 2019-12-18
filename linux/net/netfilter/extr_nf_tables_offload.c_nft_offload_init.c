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

/* Variables and functions */
 int /*<<< orphan*/  block_ing_entry ; 
 int /*<<< orphan*/  flow_indr_add_block_ing_cb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nft_offload_netdev_notifier ; 
 int register_netdevice_notifier (int /*<<< orphan*/ *) ; 

int nft_offload_init(void)
{
	int err;

	err = register_netdevice_notifier(&nft_offload_netdev_notifier);
	if (err < 0)
		return err;

	flow_indr_add_block_ing_cb(&block_ing_entry);

	return 0;
}