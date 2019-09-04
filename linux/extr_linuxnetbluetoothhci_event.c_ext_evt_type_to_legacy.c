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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR_RATELIMITED (char*,int) ; 
 int /*<<< orphan*/  LE_ADV_DIRECT_IND ; 
 int /*<<< orphan*/  LE_ADV_IND ; 
 int /*<<< orphan*/  LE_ADV_INVALID ; 
 int /*<<< orphan*/  LE_ADV_NONCONN_IND ; 
 int /*<<< orphan*/  LE_ADV_SCAN_IND ; 
 int /*<<< orphan*/  LE_ADV_SCAN_RSP ; 
 int LE_EXT_ADV_CONN_IND ; 
 int LE_EXT_ADV_DIRECT_IND ; 
 int LE_EXT_ADV_LEGACY_PDU ; 
 int LE_EXT_ADV_NON_CONN_IND ; 
 int LE_EXT_ADV_SCAN_IND ; 
 int LE_EXT_ADV_SCAN_RSP ; 
#define  LE_LEGACY_ADV_DIRECT_IND 133 
#define  LE_LEGACY_ADV_IND 132 
#define  LE_LEGACY_ADV_SCAN_IND 131 
#define  LE_LEGACY_NONCONN_IND 130 
#define  LE_LEGACY_SCAN_RSP_ADV 129 
#define  LE_LEGACY_SCAN_RSP_ADV_SCAN 128 

__attribute__((used)) static u8 ext_evt_type_to_legacy(u16 evt_type)
{
	if (evt_type & LE_EXT_ADV_LEGACY_PDU) {
		switch (evt_type) {
		case LE_LEGACY_ADV_IND:
			return LE_ADV_IND;
		case LE_LEGACY_ADV_DIRECT_IND:
			return LE_ADV_DIRECT_IND;
		case LE_LEGACY_ADV_SCAN_IND:
			return LE_ADV_SCAN_IND;
		case LE_LEGACY_NONCONN_IND:
			return LE_ADV_NONCONN_IND;
		case LE_LEGACY_SCAN_RSP_ADV:
		case LE_LEGACY_SCAN_RSP_ADV_SCAN:
			return LE_ADV_SCAN_RSP;
		}

		BT_ERR_RATELIMITED("Unknown advertising packet type: 0x%02x",
				   evt_type);

		return LE_ADV_INVALID;
	}

	if (evt_type & LE_EXT_ADV_CONN_IND) {
		if (evt_type & LE_EXT_ADV_DIRECT_IND)
			return LE_ADV_DIRECT_IND;

		return LE_ADV_IND;
	}

	if (evt_type & LE_EXT_ADV_SCAN_RSP)
		return LE_ADV_SCAN_RSP;

	if (evt_type & LE_EXT_ADV_SCAN_IND)
		return LE_ADV_SCAN_IND;

	if (evt_type == LE_EXT_ADV_NON_CONN_IND ||
	    evt_type & LE_EXT_ADV_DIRECT_IND)
		return LE_ADV_NONCONN_IND;

	BT_ERR_RATELIMITED("Unknown advertising packet type: 0x%02x",
				   evt_type);

	return LE_ADV_INVALID;
}