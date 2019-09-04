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
struct net_device {int dummy; } ;
struct bpf_offload_netdev {int /*<<< orphan*/  offdev_netdevs; int /*<<< orphan*/  l; int /*<<< orphan*/  maps; int /*<<< orphan*/  progs; struct bpf_offload_dev* offdev; struct net_device* netdev; } ;
struct bpf_offload_dev {int /*<<< orphan*/  netdevs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_devs_lock ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bpf_offload_netdev*) ; 
 struct bpf_offload_netdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  offdevs ; 
 int /*<<< orphan*/  offdevs_params ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int bpf_offload_dev_netdev_register(struct bpf_offload_dev *offdev,
				    struct net_device *netdev)
{
	struct bpf_offload_netdev *ondev;
	int err;

	ondev = kzalloc(sizeof(*ondev), GFP_KERNEL);
	if (!ondev)
		return -ENOMEM;

	ondev->netdev = netdev;
	ondev->offdev = offdev;
	INIT_LIST_HEAD(&ondev->progs);
	INIT_LIST_HEAD(&ondev->maps);

	down_write(&bpf_devs_lock);
	err = rhashtable_insert_fast(&offdevs, &ondev->l, offdevs_params);
	if (err) {
		netdev_warn(netdev, "failed to register for BPF offload\n");
		goto err_unlock_free;
	}

	list_add(&ondev->offdev_netdevs, &offdev->netdevs);
	up_write(&bpf_devs_lock);
	return 0;

err_unlock_free:
	up_write(&bpf_devs_lock);
	kfree(ondev);
	return err;
}