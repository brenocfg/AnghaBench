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
struct hci_conn {int pin_length; int key_type; void* pending_sec_level; } ;

/* Variables and functions */
 void* BT_SECURITY_FIPS ; 
 void* BT_SECURITY_HIGH ; 
 void* BT_SECURITY_MEDIUM ; 
#define  HCI_LK_AUTH_COMBINATION_P192 135 
#define  HCI_LK_AUTH_COMBINATION_P256 134 
 int HCI_LK_CHANGED_COMBINATION ; 
#define  HCI_LK_COMBINATION 133 
#define  HCI_LK_DEBUG_COMBINATION 132 
#define  HCI_LK_LOCAL_UNIT 131 
#define  HCI_LK_REMOTE_UNIT 130 
#define  HCI_LK_UNAUTH_COMBINATION_P192 129 
#define  HCI_LK_UNAUTH_COMBINATION_P256 128 

__attribute__((used)) static void conn_set_key(struct hci_conn *conn, u8 key_type, u8 pin_len)
{
	if (key_type == HCI_LK_CHANGED_COMBINATION)
		return;

	conn->pin_length = pin_len;
	conn->key_type = key_type;

	switch (key_type) {
	case HCI_LK_LOCAL_UNIT:
	case HCI_LK_REMOTE_UNIT:
	case HCI_LK_DEBUG_COMBINATION:
		return;
	case HCI_LK_COMBINATION:
		if (pin_len == 16)
			conn->pending_sec_level = BT_SECURITY_HIGH;
		else
			conn->pending_sec_level = BT_SECURITY_MEDIUM;
		break;
	case HCI_LK_UNAUTH_COMBINATION_P192:
	case HCI_LK_UNAUTH_COMBINATION_P256:
		conn->pending_sec_level = BT_SECURITY_MEDIUM;
		break;
	case HCI_LK_AUTH_COMBINATION_P192:
		conn->pending_sec_level = BT_SECURITY_HIGH;
		break;
	case HCI_LK_AUTH_COMBINATION_P256:
		conn->pending_sec_level = BT_SECURITY_FIPS;
		break;
	}
}