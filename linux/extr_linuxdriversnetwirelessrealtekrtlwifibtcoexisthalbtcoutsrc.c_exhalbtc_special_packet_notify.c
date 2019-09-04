#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_4__ {int btdm_ant_num; } ;
struct TYPE_3__ {int /*<<< orphan*/  cnt_special_packet_notify; } ;
struct btc_coexist {TYPE_2__ board_info; int /*<<< orphan*/  adapter; scalar_t__ manual_control; TYPE_1__ statistics; } ;

/* Variables and functions */
 scalar_t__ BTC_PACKET_ARP ; 
 scalar_t__ BTC_PACKET_DHCP ; 
 scalar_t__ BTC_PACKET_EAPOL ; 
 scalar_t__ BTC_PACKET_UNKNOWN ; 
 scalar_t__ IS_HARDWARE_TYPE_8192E (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_HARDWARE_TYPE_8723B (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_HARDWARE_TYPE_8821 (int /*<<< orphan*/ ) ; 
 scalar_t__ PACKET_ARP ; 
 scalar_t__ PACKET_DHCP ; 
 scalar_t__ PACKET_EAPOL ; 
 int /*<<< orphan*/  ex_btc8192e2ant_special_packet_notify (struct btc_coexist*,scalar_t__) ; 
 int /*<<< orphan*/  ex_btc8723b1ant_special_packet_notify (struct btc_coexist*,scalar_t__) ; 
 int /*<<< orphan*/  ex_btc8723b2ant_special_packet_notify (struct btc_coexist*,scalar_t__) ; 
 int /*<<< orphan*/  ex_btc8821a1ant_special_packet_notify (struct btc_coexist*,scalar_t__) ; 
 int /*<<< orphan*/  ex_btc8821a2ant_special_packet_notify (struct btc_coexist*,scalar_t__) ; 
 int /*<<< orphan*/  halbtc_is_bt_coexist_available (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc_leave_low_power (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc_normal_low_power (struct btc_coexist*) ; 

void exhalbtc_special_packet_notify(struct btc_coexist *btcoexist, u8 pkt_type)
{
	u8 packet_type;

	if (!halbtc_is_bt_coexist_available(btcoexist))
		return;
	btcoexist->statistics.cnt_special_packet_notify++;
	if (btcoexist->manual_control)
		return;

	if (pkt_type == PACKET_DHCP) {
		packet_type = BTC_PACKET_DHCP;
	} else if (pkt_type == PACKET_EAPOL) {
		packet_type = BTC_PACKET_EAPOL;
	} else if (pkt_type == PACKET_ARP) {
		packet_type = BTC_PACKET_ARP;
	} else {
		packet_type = BTC_PACKET_UNKNOWN;
		return;
	}

	halbtc_leave_low_power(btcoexist);

	if (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) {
		if (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_special_packet_notify(btcoexist,
							      packet_type);
		else if (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8821a1ant_special_packet_notify(btcoexist,
							      packet_type);
	} else if (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) {
		if (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_special_packet_notify(btcoexist,
							      packet_type);
		else if (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_special_packet_notify(btcoexist,
							      packet_type);
	} else if (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) {
		if (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8192e2ant_special_packet_notify(btcoexist,
							      packet_type);
	}

	halbtc_normal_low_power(btcoexist);
}