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
struct hci_dev {int /*<<< orphan*/  adv_instance_expire; scalar_t__ adv_instance_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cancel_adv_timeout(struct hci_dev *hdev)
{
	if (hdev->adv_instance_timeout) {
		hdev->adv_instance_timeout = 0;
		cancel_delayed_work(&hdev->adv_instance_expire);
	}
}