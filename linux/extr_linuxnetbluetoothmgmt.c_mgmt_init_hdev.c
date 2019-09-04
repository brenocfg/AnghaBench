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
struct sock {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  rpa_expired; int /*<<< orphan*/  service_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_BONDABLE ; 
 int /*<<< orphan*/  HCI_MGMT ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ hci_dev_test_and_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpa_expired ; 
 int /*<<< orphan*/  service_cache_off ; 

__attribute__((used)) static void mgmt_init_hdev(struct sock *sk, struct hci_dev *hdev)
{
	if (hci_dev_test_and_set_flag(hdev, HCI_MGMT))
		return;

	INIT_DELAYED_WORK(&hdev->service_cache, service_cache_off);
	INIT_DELAYED_WORK(&hdev->rpa_expired, rpa_expired);

	/* Non-mgmt controlled devices get this bit set
	 * implicitly so that pairing works for them, however
	 * for mgmt we require user-space to explicitly enable
	 * it
	 */
	hci_dev_clear_flag(hdev, HCI_BONDABLE);
}