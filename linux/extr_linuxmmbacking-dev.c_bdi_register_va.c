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
typedef  int /*<<< orphan*/  va_list ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct backing_dev_info {int /*<<< orphan*/  bdi_list; TYPE_1__ wb; struct device* dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  WB_registered ; 
 int /*<<< orphan*/  bdi_class ; 
 int /*<<< orphan*/  bdi_debug_register (struct backing_dev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdi_list ; 
 int /*<<< orphan*/  bdi_lock ; 
 int /*<<< orphan*/  cgwb_bdi_register (struct backing_dev_info*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct device* device_create_vargs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct backing_dev_info*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_writeback_bdi_register (struct backing_dev_info*) ; 

int bdi_register_va(struct backing_dev_info *bdi, const char *fmt, va_list args)
{
	struct device *dev;

	if (bdi->dev)	/* The driver needs to use separate queues per device */
		return 0;

	dev = device_create_vargs(bdi_class, NULL, MKDEV(0, 0), bdi, fmt, args);
	if (IS_ERR(dev))
		return PTR_ERR(dev);

	cgwb_bdi_register(bdi);
	bdi->dev = dev;

	bdi_debug_register(bdi, dev_name(dev));
	set_bit(WB_registered, &bdi->wb.state);

	spin_lock_bh(&bdi_lock);
	list_add_tail_rcu(&bdi->bdi_list, &bdi_list);
	spin_unlock_bh(&bdi_lock);

	trace_writeback_bdi_register(bdi);
	return 0;
}