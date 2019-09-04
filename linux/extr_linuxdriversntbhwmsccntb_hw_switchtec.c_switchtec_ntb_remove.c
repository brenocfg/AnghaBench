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
struct switchtec_ntb {int /*<<< orphan*/  ntb; } ;
struct switchtec_dev {struct switchtec_ntb* sndev; int /*<<< orphan*/ * link_notifier; } ;
struct device {int dummy; } ;
struct class_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  kfree (struct switchtec_ntb*) ; 
 int /*<<< orphan*/  ntb_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  switchtec_ntb_deinit_crosslink (struct switchtec_ntb*) ; 
 int /*<<< orphan*/  switchtec_ntb_deinit_db_msg_irq (struct switchtec_ntb*) ; 
 int /*<<< orphan*/  switchtec_ntb_deinit_shared_mw (struct switchtec_ntb*) ; 
 struct switchtec_dev* to_stdev (struct device*) ; 

__attribute__((used)) static void switchtec_ntb_remove(struct device *dev,
				 struct class_interface *class_intf)
{
	struct switchtec_dev *stdev = to_stdev(dev);
	struct switchtec_ntb *sndev = stdev->sndev;

	if (!sndev)
		return;

	stdev->link_notifier = NULL;
	stdev->sndev = NULL;
	ntb_unregister_device(&sndev->ntb);
	switchtec_ntb_deinit_db_msg_irq(sndev);
	switchtec_ntb_deinit_shared_mw(sndev);
	switchtec_ntb_deinit_crosslink(sndev);
	kfree(sndev);
	dev_info(dev, "ntb device unregistered\n");
}