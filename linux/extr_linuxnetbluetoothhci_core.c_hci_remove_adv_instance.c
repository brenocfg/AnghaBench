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
typedef  int u8 ;
struct hci_dev {int cur_adv_instance; int /*<<< orphan*/  adv_instance_cnt; scalar_t__ adv_instance_timeout; int /*<<< orphan*/  adv_instance_expire; int /*<<< orphan*/  name; } ;
struct adv_info {int /*<<< orphan*/  list; int /*<<< orphan*/  rpa_expired_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
 int ENOENT ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct adv_info* hci_find_adv_instance (struct hci_dev*,int) ; 
 int /*<<< orphan*/  kfree (struct adv_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

int hci_remove_adv_instance(struct hci_dev *hdev, u8 instance)
{
	struct adv_info *adv_instance;

	adv_instance = hci_find_adv_instance(hdev, instance);
	if (!adv_instance)
		return -ENOENT;

	BT_DBG("%s removing %dMR", hdev->name, instance);

	if (hdev->cur_adv_instance == instance) {
		if (hdev->adv_instance_timeout) {
			cancel_delayed_work(&hdev->adv_instance_expire);
			hdev->adv_instance_timeout = 0;
		}
		hdev->cur_adv_instance = 0x00;
	}

	cancel_delayed_work_sync(&adv_instance->rpa_expired_cb);

	list_del(&adv_instance->list);
	kfree(adv_instance);

	hdev->adv_instance_cnt--;

	return 0;
}