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
struct hci_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  kfree (struct hci_dev*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct hci_dev* to_hci_dev (struct device*) ; 

__attribute__((used)) static void bt_host_release(struct device *dev)
{
	struct hci_dev *hdev = to_hci_dev(dev);
	kfree(hdev);
	module_put(THIS_MODULE);
}