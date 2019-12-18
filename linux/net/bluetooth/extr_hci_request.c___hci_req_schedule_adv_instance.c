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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct hci_request {struct hci_dev* hdev; } ;
struct hci_dev {int adv_instance_timeout; int /*<<< orphan*/  cur_adv_instance; int /*<<< orphan*/  adv_instance_expire; int /*<<< orphan*/  req_workqueue; int /*<<< orphan*/  adv_instances; } ;
struct adv_info {scalar_t__ timeout; scalar_t__ duration; scalar_t__ remaining_time; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  HCI_ADVERTISING ; 
 int /*<<< orphan*/  HCI_LE_ADV ; 
 int /*<<< orphan*/  __hci_req_enable_advertising (struct hci_request*) ; 
 int /*<<< orphan*/  __hci_req_start_ext_adv (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __hci_req_update_adv_data (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __hci_req_update_scan_rsp_data (struct hci_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext_adv_capable (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct adv_info* hci_find_adv_instance (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int __hci_req_schedule_adv_instance(struct hci_request *req, u8 instance,
				    bool force)
{
	struct hci_dev *hdev = req->hdev;
	struct adv_info *adv_instance = NULL;
	u16 timeout;

	if (hci_dev_test_flag(hdev, HCI_ADVERTISING) ||
	    list_empty(&hdev->adv_instances))
		return -EPERM;

	if (hdev->adv_instance_timeout)
		return -EBUSY;

	adv_instance = hci_find_adv_instance(hdev, instance);
	if (!adv_instance)
		return -ENOENT;

	/* A zero timeout means unlimited advertising. As long as there is
	 * only one instance, duration should be ignored. We still set a timeout
	 * in case further instances are being added later on.
	 *
	 * If the remaining lifetime of the instance is more than the duration
	 * then the timeout corresponds to the duration, otherwise it will be
	 * reduced to the remaining instance lifetime.
	 */
	if (adv_instance->timeout == 0 ||
	    adv_instance->duration <= adv_instance->remaining_time)
		timeout = adv_instance->duration;
	else
		timeout = adv_instance->remaining_time;

	/* The remaining time is being reduced unless the instance is being
	 * advertised without time limit.
	 */
	if (adv_instance->timeout)
		adv_instance->remaining_time =
				adv_instance->remaining_time - timeout;

	/* Only use work for scheduling instances with legacy advertising */
	if (!ext_adv_capable(hdev)) {
		hdev->adv_instance_timeout = timeout;
		queue_delayed_work(hdev->req_workqueue,
			   &hdev->adv_instance_expire,
			   msecs_to_jiffies(timeout * 1000));
	}

	/* If we're just re-scheduling the same instance again then do not
	 * execute any HCI commands. This happens when a single instance is
	 * being advertised.
	 */
	if (!force && hdev->cur_adv_instance == instance &&
	    hci_dev_test_flag(hdev, HCI_LE_ADV))
		return 0;

	hdev->cur_adv_instance = instance;
	if (ext_adv_capable(hdev)) {
		__hci_req_start_ext_adv(req, instance);
	} else {
		__hci_req_update_adv_data(req, instance);
		__hci_req_update_scan_rsp_data(req, instance);
		__hci_req_enable_advertising(req);
	}

	return 0;
}