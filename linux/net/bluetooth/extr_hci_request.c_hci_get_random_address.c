#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {int* b; } ;
struct hci_dev {int rpa_timeout; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  rpa_expired; int /*<<< orphan*/  workqueue; TYPE_1__ rpa; int /*<<< orphan*/  name; int /*<<< orphan*/  irk; int /*<<< orphan*/  random_addr; } ;
struct adv_info {int rpa_expired; int /*<<< orphan*/  rpa_expired_cb; int /*<<< orphan*/  random_addr; } ;
typedef  TYPE_1__ bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_LE_DEV_PUBLIC ; 
 int /*<<< orphan*/  ADDR_LE_DEV_RANDOM ; 
 TYPE_1__* BDADDR_ANY ; 
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_RPA_EXPIRED ; 
 scalar_t__ bacmp (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  bacpy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  get_random_bytes (TYPE_1__*,int) ; 
 int /*<<< orphan*/  hci_dev_test_and_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int smp_generate_rpa (struct hci_dev*,int /*<<< orphan*/ ,TYPE_1__*) ; 

int hci_get_random_address(struct hci_dev *hdev, bool require_privacy,
			   bool use_rpa, struct adv_info *adv_instance,
			   u8 *own_addr_type, bdaddr_t *rand_addr)
{
	int err;

	bacpy(rand_addr, BDADDR_ANY);

	/* If privacy is enabled use a resolvable private address. If
	 * current RPA has expired then generate a new one.
	 */
	if (use_rpa) {
		int to;

		*own_addr_type = ADDR_LE_DEV_RANDOM;

		if (adv_instance) {
			if (!adv_instance->rpa_expired &&
			    !bacmp(&adv_instance->random_addr, &hdev->rpa))
				return 0;

			adv_instance->rpa_expired = false;
		} else {
			if (!hci_dev_test_and_clear_flag(hdev, HCI_RPA_EXPIRED) &&
			    !bacmp(&hdev->random_addr, &hdev->rpa))
				return 0;
		}

		err = smp_generate_rpa(hdev, hdev->irk, &hdev->rpa);
		if (err < 0) {
			BT_ERR("%s failed to generate new RPA", hdev->name);
			return err;
		}

		bacpy(rand_addr, &hdev->rpa);

		to = msecs_to_jiffies(hdev->rpa_timeout * 1000);
		if (adv_instance)
			queue_delayed_work(hdev->workqueue,
					   &adv_instance->rpa_expired_cb, to);
		else
			queue_delayed_work(hdev->workqueue,
					   &hdev->rpa_expired, to);

		return 0;
	}

	/* In case of required privacy without resolvable private address,
	 * use an non-resolvable private address. This is useful for
	 * non-connectable advertising.
	 */
	if (require_privacy) {
		bdaddr_t nrpa;

		while (true) {
			/* The non-resolvable private address is generated
			 * from random six bytes with the two most significant
			 * bits cleared.
			 */
			get_random_bytes(&nrpa, 6);
			nrpa.b[5] &= 0x3f;

			/* The non-resolvable private address shall not be
			 * equal to the public address.
			 */
			if (bacmp(&hdev->bdaddr, &nrpa))
				break;
		}

		*own_addr_type = ADDR_LE_DEV_RANDOM;
		bacpy(rand_addr, &nrpa);

		return 0;
	}

	/* No privacy so use a public address. */
	*own_addr_type = ADDR_LE_DEV_PUBLIC;

	return 0;
}