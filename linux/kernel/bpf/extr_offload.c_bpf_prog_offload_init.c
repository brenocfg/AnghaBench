#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union bpf_attr {scalar_t__ prog_type; int /*<<< orphan*/  prog_ifindex; scalar_t__ prog_flags; } ;
struct bpf_prog_offload {scalar_t__ netdev; int /*<<< orphan*/  offloads; int /*<<< orphan*/  offdev; struct bpf_prog* prog; } ;
struct bpf_prog {TYPE_2__* aux; } ;
struct bpf_offload_netdev {int /*<<< orphan*/  progs; int /*<<< orphan*/  offdev; } ;
struct TYPE_6__ {TYPE_1__* nsproxy; } ;
struct TYPE_5__ {struct bpf_prog_offload* offload; } ;
struct TYPE_4__ {int /*<<< orphan*/  net_ns; } ;

/* Variables and functions */
 scalar_t__ BPF_PROG_TYPE_SCHED_CLS ; 
 scalar_t__ BPF_PROG_TYPE_XDP ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_USER ; 
 int bpf_dev_offload_check (scalar_t__) ; 
 int /*<<< orphan*/  bpf_devs_lock ; 
 struct bpf_offload_netdev* bpf_offload_find_netdev (scalar_t__) ; 
 TYPE_3__* current ; 
 scalar_t__ dev_get_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (scalar_t__) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bpf_prog_offload*) ; 
 struct bpf_prog_offload* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int bpf_prog_offload_init(struct bpf_prog *prog, union bpf_attr *attr)
{
	struct bpf_offload_netdev *ondev;
	struct bpf_prog_offload *offload;
	int err;

	if (attr->prog_type != BPF_PROG_TYPE_SCHED_CLS &&
	    attr->prog_type != BPF_PROG_TYPE_XDP)
		return -EINVAL;

	if (attr->prog_flags)
		return -EINVAL;

	offload = kzalloc(sizeof(*offload), GFP_USER);
	if (!offload)
		return -ENOMEM;

	offload->prog = prog;

	offload->netdev = dev_get_by_index(current->nsproxy->net_ns,
					   attr->prog_ifindex);
	err = bpf_dev_offload_check(offload->netdev);
	if (err)
		goto err_maybe_put;

	down_write(&bpf_devs_lock);
	ondev = bpf_offload_find_netdev(offload->netdev);
	if (!ondev) {
		err = -EINVAL;
		goto err_unlock;
	}
	offload->offdev = ondev->offdev;
	prog->aux->offload = offload;
	list_add_tail(&offload->offloads, &ondev->progs);
	dev_put(offload->netdev);
	up_write(&bpf_devs_lock);

	return 0;
err_unlock:
	up_write(&bpf_devs_lock);
err_maybe_put:
	if (offload->netdev)
		dev_put(offload->netdev);
	kfree(offload);
	return err;
}