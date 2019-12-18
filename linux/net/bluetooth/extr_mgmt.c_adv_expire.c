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
typedef  int u32 ;
struct hci_request {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  cur_adv_instance; } ;
struct adv_info {int flags; int /*<<< orphan*/  instance; } ;

/* Variables and functions */
 int __hci_req_schedule_adv_instance (struct hci_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cancel_adv_timeout (struct hci_dev*) ; 
 struct adv_info* hci_find_adv_instance (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct adv_info* hci_get_next_instance (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_run (struct hci_request*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adv_expire(struct hci_dev *hdev, u32 flags)
{
	struct adv_info *adv_instance;
	struct hci_request req;
	int err;

	adv_instance = hci_find_adv_instance(hdev, hdev->cur_adv_instance);
	if (!adv_instance)
		return;

	/* stop if current instance doesn't need to be changed */
	if (!(adv_instance->flags & flags))
		return;

	cancel_adv_timeout(hdev);

	adv_instance = hci_get_next_instance(hdev, adv_instance->instance);
	if (!adv_instance)
		return;

	hci_req_init(&req, hdev);
	err = __hci_req_schedule_adv_instance(&req, adv_instance->instance,
					      true);
	if (err)
		return;

	hci_req_run(&req, NULL);
}