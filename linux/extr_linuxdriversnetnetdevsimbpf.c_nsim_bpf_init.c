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
struct netdevsim {int bpf_bind_accept; int bpf_tc_accept; int bpf_tc_non_bound_accept; int bpf_xdpdrv_accept; int bpf_xdpoffload_accept; int bpf_map_accept; TYPE_1__* sdev; int /*<<< orphan*/  ddir; int /*<<< orphan*/  bpf_bind_verifier_delay; int /*<<< orphan*/  bpf_offloaded_id; int /*<<< orphan*/  netdev; } ;
struct TYPE_2__ {int refcnt; int /*<<< orphan*/  bpf_dev; int /*<<< orphan*/  ddir_bpf_bound_progs; int /*<<< orphan*/  ddir; int /*<<< orphan*/  bpf_bound_maps; int /*<<< orphan*/  bpf_bound_progs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_offload_dev_create () ; 
 int /*<<< orphan*/  bpf_offload_dev_destroy (int /*<<< orphan*/ ) ; 
 int bpf_offload_dev_netdev_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nsim_bpf_init(struct netdevsim *ns)
{
	int err;

	if (ns->sdev->refcnt == 1) {
		INIT_LIST_HEAD(&ns->sdev->bpf_bound_progs);
		INIT_LIST_HEAD(&ns->sdev->bpf_bound_maps);

		ns->sdev->ddir_bpf_bound_progs =
			debugfs_create_dir("bpf_bound_progs", ns->sdev->ddir);
		if (IS_ERR_OR_NULL(ns->sdev->ddir_bpf_bound_progs))
			return -ENOMEM;

		ns->sdev->bpf_dev = bpf_offload_dev_create();
		err = PTR_ERR_OR_ZERO(ns->sdev->bpf_dev);
		if (err)
			return err;
	}

	err = bpf_offload_dev_netdev_register(ns->sdev->bpf_dev, ns->netdev);
	if (err)
		goto err_destroy_bdev;

	debugfs_create_u32("bpf_offloaded_id", 0400, ns->ddir,
			   &ns->bpf_offloaded_id);

	ns->bpf_bind_accept = true;
	debugfs_create_bool("bpf_bind_accept", 0600, ns->ddir,
			    &ns->bpf_bind_accept);
	debugfs_create_u32("bpf_bind_verifier_delay", 0600, ns->ddir,
			   &ns->bpf_bind_verifier_delay);

	ns->bpf_tc_accept = true;
	debugfs_create_bool("bpf_tc_accept", 0600, ns->ddir,
			    &ns->bpf_tc_accept);
	debugfs_create_bool("bpf_tc_non_bound_accept", 0600, ns->ddir,
			    &ns->bpf_tc_non_bound_accept);
	ns->bpf_xdpdrv_accept = true;
	debugfs_create_bool("bpf_xdpdrv_accept", 0600, ns->ddir,
			    &ns->bpf_xdpdrv_accept);
	ns->bpf_xdpoffload_accept = true;
	debugfs_create_bool("bpf_xdpoffload_accept", 0600, ns->ddir,
			    &ns->bpf_xdpoffload_accept);

	ns->bpf_map_accept = true;
	debugfs_create_bool("bpf_map_accept", 0600, ns->ddir,
			    &ns->bpf_map_accept);

	return 0;

err_destroy_bdev:
	if (ns->sdev->refcnt == 1)
		bpf_offload_dev_destroy(ns->sdev->bpf_dev);
	return err;
}