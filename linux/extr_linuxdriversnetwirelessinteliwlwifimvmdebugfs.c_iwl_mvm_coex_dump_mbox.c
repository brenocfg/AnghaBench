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
struct iwl_bt_coex_profile_notif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A2DP_SRC ; 
 int /*<<< orphan*/  A2DP_STATE ; 
 int /*<<< orphan*/  ACL_STATE ; 
 int /*<<< orphan*/  AGGR_TRFC_LD ; 
 int /*<<< orphan*/  BR_MAX_TX_POWER ; 
 int /*<<< orphan*/  BT_MBOX_PRINT (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CHL_SEQN_LSB ; 
 int /*<<< orphan*/  CHL_SEQ_N ; 
 int /*<<< orphan*/  CONN ; 
 int /*<<< orphan*/  DISC ; 
 int /*<<< orphan*/  ESCO_RE_TX ; 
 int /*<<< orphan*/  INBAND_P ; 
 int /*<<< orphan*/  INBAND_S ; 
 int /*<<< orphan*/  INQUIRY ; 
 int /*<<< orphan*/  IP_SR ; 
 int /*<<< orphan*/  LE_ADV ; 
 int /*<<< orphan*/  LE_MAX_TX_POWER ; 
 int /*<<< orphan*/  LE_MIN_RSSI ; 
 int /*<<< orphan*/  LE_MSTR ; 
 int /*<<< orphan*/  LE_PROF1 ; 
 int /*<<< orphan*/  LE_PROF2 ; 
 int /*<<< orphan*/  LE_PROF_OTHER ; 
 int /*<<< orphan*/  LE_SCAN ; 
 int /*<<< orphan*/  LE_SLAVE_LAT ; 
 int /*<<< orphan*/  MSG_TYPE ; 
 int /*<<< orphan*/  MSG_TYPE_2 ; 
 int /*<<< orphan*/  MSTR_STATE ; 
 int /*<<< orphan*/  OBX_STATE ; 
 int /*<<< orphan*/  OPEN_CON_1 ; 
 int /*<<< orphan*/  OPEN_CON_2 ; 
 int /*<<< orphan*/  PAG ; 
 int /*<<< orphan*/  SCO_DURATION ; 
 int /*<<< orphan*/  SCO_RX_ACT ; 
 int /*<<< orphan*/  SCO_STATE ; 
 int /*<<< orphan*/  SCO_TX_ACT ; 
 int /*<<< orphan*/  SNIFF_ACT ; 
 int /*<<< orphan*/  SNIFF_INTERVAL ; 
 int /*<<< orphan*/  SNIFF_STATE ; 
 int /*<<< orphan*/  SSN ; 
 int /*<<< orphan*/  SSN_2 ; 
 int /*<<< orphan*/  TRAFFIC_LOAD ; 
 int /*<<< orphan*/  UPDATE_REQUEST ; 
 scalar_t__ scnprintf (char*,int,char*) ; 

__attribute__((used)) static
int iwl_mvm_coex_dump_mbox(struct iwl_bt_coex_profile_notif *notif, char *buf,
			   int pos, int bufsz)
{
	pos += scnprintf(buf+pos, bufsz-pos, "MBOX dw0:\n");

	BT_MBOX_PRINT(0, LE_SLAVE_LAT, false);
	BT_MBOX_PRINT(0, LE_PROF1, false);
	BT_MBOX_PRINT(0, LE_PROF2, false);
	BT_MBOX_PRINT(0, LE_PROF_OTHER, false);
	BT_MBOX_PRINT(0, CHL_SEQ_N, false);
	BT_MBOX_PRINT(0, INBAND_S, false);
	BT_MBOX_PRINT(0, LE_MIN_RSSI, false);
	BT_MBOX_PRINT(0, LE_SCAN, false);
	BT_MBOX_PRINT(0, LE_ADV, false);
	BT_MBOX_PRINT(0, LE_MAX_TX_POWER, false);
	BT_MBOX_PRINT(0, OPEN_CON_1, true);

	pos += scnprintf(buf+pos, bufsz-pos, "MBOX dw1:\n");

	BT_MBOX_PRINT(1, BR_MAX_TX_POWER, false);
	BT_MBOX_PRINT(1, IP_SR, false);
	BT_MBOX_PRINT(1, LE_MSTR, false);
	BT_MBOX_PRINT(1, AGGR_TRFC_LD, false);
	BT_MBOX_PRINT(1, MSG_TYPE, false);
	BT_MBOX_PRINT(1, SSN, true);

	pos += scnprintf(buf+pos, bufsz-pos, "MBOX dw2:\n");

	BT_MBOX_PRINT(2, SNIFF_ACT, false);
	BT_MBOX_PRINT(2, PAG, false);
	BT_MBOX_PRINT(2, INQUIRY, false);
	BT_MBOX_PRINT(2, CONN, false);
	BT_MBOX_PRINT(2, SNIFF_INTERVAL, false);
	BT_MBOX_PRINT(2, DISC, false);
	BT_MBOX_PRINT(2, SCO_TX_ACT, false);
	BT_MBOX_PRINT(2, SCO_RX_ACT, false);
	BT_MBOX_PRINT(2, ESCO_RE_TX, false);
	BT_MBOX_PRINT(2, SCO_DURATION, true);

	pos += scnprintf(buf+pos, bufsz-pos, "MBOX dw3:\n");

	BT_MBOX_PRINT(3, SCO_STATE, false);
	BT_MBOX_PRINT(3, SNIFF_STATE, false);
	BT_MBOX_PRINT(3, A2DP_STATE, false);
	BT_MBOX_PRINT(3, A2DP_SRC, false);
	BT_MBOX_PRINT(3, ACL_STATE, false);
	BT_MBOX_PRINT(3, MSTR_STATE, false);
	BT_MBOX_PRINT(3, OBX_STATE, false);
	BT_MBOX_PRINT(3, OPEN_CON_2, false);
	BT_MBOX_PRINT(3, TRAFFIC_LOAD, false);
	BT_MBOX_PRINT(3, CHL_SEQN_LSB, false);
	BT_MBOX_PRINT(3, INBAND_P, false);
	BT_MBOX_PRINT(3, MSG_TYPE_2, false);
	BT_MBOX_PRINT(3, SSN_2, false);
	BT_MBOX_PRINT(3, UPDATE_REQUEST, true);

	return pos;
}