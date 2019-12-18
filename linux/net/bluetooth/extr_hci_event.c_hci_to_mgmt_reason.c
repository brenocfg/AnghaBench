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

/* Variables and functions */
#define  HCI_ERROR_CONNECTION_TIMEOUT 132 
#define  HCI_ERROR_LOCAL_HOST_TERM 131 
#define  HCI_ERROR_REMOTE_LOW_RESOURCES 130 
#define  HCI_ERROR_REMOTE_POWER_OFF 129 
#define  HCI_ERROR_REMOTE_USER_TERM 128 
 int MGMT_DEV_DISCONN_LOCAL_HOST ; 
 int MGMT_DEV_DISCONN_REMOTE ; 
 int MGMT_DEV_DISCONN_TIMEOUT ; 
 int MGMT_DEV_DISCONN_UNKNOWN ; 

__attribute__((used)) static u8 hci_to_mgmt_reason(u8 err)
{
	switch (err) {
	case HCI_ERROR_CONNECTION_TIMEOUT:
		return MGMT_DEV_DISCONN_TIMEOUT;
	case HCI_ERROR_REMOTE_USER_TERM:
	case HCI_ERROR_REMOTE_LOW_RESOURCES:
	case HCI_ERROR_REMOTE_POWER_OFF:
		return MGMT_DEV_DISCONN_REMOTE;
	case HCI_ERROR_LOCAL_HOST_TERM:
		return MGMT_DEV_DISCONN_LOCAL_HOST;
	default:
		return MGMT_DEV_DISCONN_UNKNOWN;
	}
}