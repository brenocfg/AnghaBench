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
typedef  int u32 ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int HCI_MAX_AD_LENGTH ; 
 int MGMT_ADV_FLAG_APPEARANCE ; 
 int MGMT_ADV_FLAG_DISCOV ; 
 int MGMT_ADV_FLAG_LIMITED_DISCOV ; 
 int MGMT_ADV_FLAG_LOCAL_NAME ; 
 int MGMT_ADV_FLAG_MANAGED_FLAGS ; 
 int MGMT_ADV_FLAG_TX_POWER ; 
 scalar_t__ calculate_name_len (struct hci_dev*) ; 

__attribute__((used)) static u8 tlv_data_max_len(struct hci_dev *hdev, u32 adv_flags,
			   bool is_adv_data)
{
	u8 max_len = HCI_MAX_AD_LENGTH;

	if (is_adv_data) {
		if (adv_flags & (MGMT_ADV_FLAG_DISCOV |
				 MGMT_ADV_FLAG_LIMITED_DISCOV |
				 MGMT_ADV_FLAG_MANAGED_FLAGS))
			max_len -= 3;

		if (adv_flags & MGMT_ADV_FLAG_TX_POWER)
			max_len -= 3;
	} else {
		if (adv_flags & MGMT_ADV_FLAG_LOCAL_NAME)
			max_len -= calculate_name_len(hdev);

		if (adv_flags & (MGMT_ADV_FLAG_APPEARANCE))
			max_len -= 4;
	}

	return max_len;
}