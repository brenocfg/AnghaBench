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
typedef  int u64 ;
struct hci_dev {int auth_payload_timeout; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 

__attribute__((used)) static int auth_payload_timeout_set(void *data, u64 val)
{
	struct hci_dev *hdev = data;

	if (val < 0x0001 || val > 0xffff)
		return -EINVAL;

	hci_dev_lock(hdev);
	hdev->auth_payload_timeout = val;
	hci_dev_unlock(hdev);

	return 0;
}