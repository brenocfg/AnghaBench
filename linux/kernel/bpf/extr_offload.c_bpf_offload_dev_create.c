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
struct bpf_prog_offload_ops {int dummy; } ;
struct bpf_offload_dev {int /*<<< orphan*/  netdevs; void* priv; struct bpf_prog_offload_ops const* ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct bpf_offload_dev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_devs_lock ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct bpf_offload_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offdevs ; 
 int offdevs_inited ; 
 int /*<<< orphan*/  offdevs_params ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

struct bpf_offload_dev *
bpf_offload_dev_create(const struct bpf_prog_offload_ops *ops, void *priv)
{
	struct bpf_offload_dev *offdev;
	int err;

	down_write(&bpf_devs_lock);
	if (!offdevs_inited) {
		err = rhashtable_init(&offdevs, &offdevs_params);
		if (err)
			return ERR_PTR(err);
		offdevs_inited = true;
	}
	up_write(&bpf_devs_lock);

	offdev = kzalloc(sizeof(*offdev), GFP_KERNEL);
	if (!offdev)
		return ERR_PTR(-ENOMEM);

	offdev->ops = ops;
	offdev->priv = priv;
	INIT_LIST_HEAD(&offdev->netdevs);

	return offdev;
}