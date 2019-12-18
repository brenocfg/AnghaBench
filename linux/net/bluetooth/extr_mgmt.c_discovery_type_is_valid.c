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
typedef  int uint8_t ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
#define  DISCOV_TYPE_BREDR 130 
#define  DISCOV_TYPE_INTERLEAVED 129 
#define  DISCOV_TYPE_LE 128 
 int MGMT_STATUS_INVALID_PARAMS ; 
 int mgmt_bredr_support (struct hci_dev*) ; 
 int mgmt_le_support (struct hci_dev*) ; 

__attribute__((used)) static bool discovery_type_is_valid(struct hci_dev *hdev, uint8_t type,
				    uint8_t *mgmt_status)
{
	switch (type) {
	case DISCOV_TYPE_LE:
		*mgmt_status = mgmt_le_support(hdev);
		if (*mgmt_status)
			return false;
		break;
	case DISCOV_TYPE_INTERLEAVED:
		*mgmt_status = mgmt_le_support(hdev);
		if (*mgmt_status)
			return false;
		/* Intentional fall-through */
	case DISCOV_TYPE_BREDR:
		*mgmt_status = mgmt_bredr_support(hdev);
		if (*mgmt_status)
			return false;
		break;
	default:
		*mgmt_status = MGMT_STATUS_INVALID_PARAMS;
		return false;
	}

	return true;
}