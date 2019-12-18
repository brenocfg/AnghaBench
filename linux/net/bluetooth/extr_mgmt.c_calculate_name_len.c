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
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_MAX_SHORT_NAME_LENGTH ; 
 int /*<<< orphan*/  append_local_name (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 calculate_name_len(struct hci_dev *hdev)
{
	u8 buf[HCI_MAX_SHORT_NAME_LENGTH + 3];

	return append_local_name(hdev, buf, 0);
}