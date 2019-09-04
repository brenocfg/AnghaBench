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
struct tb_regs_switch_header {int dummy; } ;
struct tb_regs_port_header {int dummy; } ;
struct tb_regs_hop {int dummy; } ;
struct tb_nhi {TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  groups; int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * parent; } ;
struct tb {scalar_t__ index; TYPE_2__ dev; int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; struct tb_nhi* nhi; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  domain_attr_groups ; 
 scalar_t__ ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct tb*) ; 
 struct tb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_bus_type ; 
 int /*<<< orphan*/  tb_domain_ida ; 
 int /*<<< orphan*/  tb_domain_type ; 

struct tb *tb_domain_alloc(struct tb_nhi *nhi, size_t privsize)
{
	struct tb *tb;

	/*
	 * Make sure the structure sizes map with that the hardware
	 * expects because bit-fields are being used.
	 */
	BUILD_BUG_ON(sizeof(struct tb_regs_switch_header) != 5 * 4);
	BUILD_BUG_ON(sizeof(struct tb_regs_port_header) != 8 * 4);
	BUILD_BUG_ON(sizeof(struct tb_regs_hop) != 2 * 4);

	tb = kzalloc(sizeof(*tb) + privsize, GFP_KERNEL);
	if (!tb)
		return NULL;

	tb->nhi = nhi;
	mutex_init(&tb->lock);

	tb->index = ida_simple_get(&tb_domain_ida, 0, 0, GFP_KERNEL);
	if (tb->index < 0)
		goto err_free;

	tb->wq = alloc_ordered_workqueue("thunderbolt%d", 0, tb->index);
	if (!tb->wq)
		goto err_remove_ida;

	tb->dev.parent = &nhi->pdev->dev;
	tb->dev.bus = &tb_bus_type;
	tb->dev.type = &tb_domain_type;
	tb->dev.groups = domain_attr_groups;
	dev_set_name(&tb->dev, "domain%d", tb->index);
	device_initialize(&tb->dev);

	return tb;

err_remove_ida:
	ida_simple_remove(&tb_domain_ida, tb->index);
err_free:
	kfree(tb);

	return NULL;
}