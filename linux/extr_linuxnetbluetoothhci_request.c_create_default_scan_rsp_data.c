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
struct hci_dev {scalar_t__ appearance; } ;

/* Variables and functions */
 int /*<<< orphan*/  append_appearance (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_local_name (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 create_default_scan_rsp_data(struct hci_dev *hdev, u8 *ptr)
{
	u8 scan_rsp_len = 0;

	if (hdev->appearance) {
		scan_rsp_len = append_appearance(hdev, ptr, scan_rsp_len);
	}

	return append_local_name(hdev, ptr, scan_rsp_len);
}