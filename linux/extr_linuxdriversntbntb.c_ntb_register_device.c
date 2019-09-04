#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * bus; } ;
struct ntb_dev {TYPE_2__ dev; int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/ * ctx_ops; int /*<<< orphan*/ * ctx; TYPE_1__* pdev; int /*<<< orphan*/  released; int /*<<< orphan*/  ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_bus ; 
 int /*<<< orphan*/  ntb_dev_ops_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_dev_release ; 
 int /*<<< orphan*/  pci_name (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ntb_register_device(struct ntb_dev *ntb)
{
	if (!ntb)
		return -EINVAL;
	if (!ntb->pdev)
		return -EINVAL;
	if (!ntb->ops)
		return -EINVAL;
	if (!ntb_dev_ops_is_valid(ntb->ops))
		return -EINVAL;

	init_completion(&ntb->released);

	ntb->dev.bus = &ntb_bus;
	ntb->dev.parent = &ntb->pdev->dev;
	ntb->dev.release = ntb_dev_release;
	dev_set_name(&ntb->dev, "%s", pci_name(ntb->pdev));

	ntb->ctx = NULL;
	ntb->ctx_ops = NULL;
	spin_lock_init(&ntb->ctx_lock);

	return device_register(&ntb->dev);
}