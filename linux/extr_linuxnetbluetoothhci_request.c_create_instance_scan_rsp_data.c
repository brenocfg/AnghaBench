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
typedef  size_t u8 ;
typedef  int u32 ;
struct hci_dev {scalar_t__ appearance; } ;
struct adv_info {int flags; scalar_t__ scan_rsp_len; int /*<<< orphan*/  scan_rsp_data; } ;

/* Variables and functions */
 int MGMT_ADV_FLAG_APPEARANCE ; 
 int MGMT_ADV_FLAG_LOCAL_NAME ; 
 size_t append_appearance (struct hci_dev*,size_t*,size_t) ; 
 size_t append_local_name (struct hci_dev*,size_t*,size_t) ; 
 struct adv_info* hci_find_adv_instance (struct hci_dev*,size_t) ; 
 int /*<<< orphan*/  memcpy (size_t*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u8 create_instance_scan_rsp_data(struct hci_dev *hdev, u8 instance,
					u8 *ptr)
{
	struct adv_info *adv_instance;
	u32 instance_flags;
	u8 scan_rsp_len = 0;

	adv_instance = hci_find_adv_instance(hdev, instance);
	if (!adv_instance)
		return 0;

	instance_flags = adv_instance->flags;

	if ((instance_flags & MGMT_ADV_FLAG_APPEARANCE) && hdev->appearance) {
		scan_rsp_len = append_appearance(hdev, ptr, scan_rsp_len);
	}

	memcpy(&ptr[scan_rsp_len], adv_instance->scan_rsp_data,
	       adv_instance->scan_rsp_len);

	scan_rsp_len += adv_instance->scan_rsp_len;

	if (instance_flags & MGMT_ADV_FLAG_LOCAL_NAME)
		scan_rsp_len = append_local_name(hdev, ptr, scan_rsp_len);

	return scan_rsp_len;
}