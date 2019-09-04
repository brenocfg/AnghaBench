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
typedef  scalar_t__ u64 ;
struct hci_dev {scalar_t__ sniff_min_interval; scalar_t__ sniff_max_interval; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 

__attribute__((used)) static int sniff_max_interval_set(void *data, u64 val)
{
	struct hci_dev *hdev = data;

	if (val == 0 || val % 2 || val < hdev->sniff_min_interval)
		return -EINVAL;

	hci_dev_lock(hdev);
	hdev->sniff_max_interval = val;
	hci_dev_unlock(hdev);

	return 0;
}