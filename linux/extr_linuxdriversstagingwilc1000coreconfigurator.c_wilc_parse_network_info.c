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
typedef  char u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct network_info {char rssi; int tsf_hi; char dtim_period; scalar_t__ ies_len; int /*<<< orphan*/  ies; int /*<<< orphan*/  beacon_period; int /*<<< orphan*/  ch; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; void* tsf_lo; int /*<<< orphan*/  cap_info; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 char BEACON_INTERVAL_LEN ; 
 char CAP_INFO_LEN ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ FCS_LEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char MAC_HDR_LEN ; 
 scalar_t__ MAKE_WORD16 (char,char) ; 
 size_t TAG_PARAM_OFFSET ; 
 char TIME_STAMP_LEN ; 
 int /*<<< orphan*/  get_BSSID (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_beacon_period (char*) ; 
 int get_beacon_timestamp_hi (char*) ; 
 void* get_beacon_timestamp_lo (char*) ; 
 int /*<<< orphan*/  get_cap_info (char*) ; 
 int /*<<< orphan*/  get_current_channel_802_11n (char*,scalar_t__) ; 
 int /*<<< orphan*/  get_ssid (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* get_tim_elm (char*,scalar_t__,char) ; 
 int /*<<< orphan*/  kfree (struct network_info*) ; 
 int /*<<< orphan*/  kmemdup (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct network_info* kzalloc (int,int /*<<< orphan*/ ) ; 

s32 wilc_parse_network_info(u8 *msg_buffer,
			    struct network_info **ret_network_info)
{
	struct network_info *network_info;
	u8 *wid_val, *msa, *tim_elm, *ies;
	u32 tsf_lo, tsf_hi;
	u16 wid_len, rx_len, ies_len;
	u8 msg_type, index;

	msg_type = msg_buffer[0];

	if ('N' != msg_type)
		return -EFAULT;

	wid_len = MAKE_WORD16(msg_buffer[6], msg_buffer[7]);
	wid_val = &msg_buffer[8];

	network_info = kzalloc(sizeof(*network_info), GFP_KERNEL);
	if (!network_info)
		return -ENOMEM;

	network_info->rssi = wid_val[0];

	msa = &wid_val[1];

	rx_len = wid_len - 1;
	network_info->cap_info = get_cap_info(msa);
	network_info->tsf_lo = get_beacon_timestamp_lo(msa);

	tsf_lo = get_beacon_timestamp_lo(msa);
	tsf_hi = get_beacon_timestamp_hi(msa);

	network_info->tsf_hi = tsf_lo | ((u64)tsf_hi << 32);

	get_ssid(msa, network_info->ssid, &network_info->ssid_len);
	get_BSSID(msa, network_info->bssid);

	network_info->ch = get_current_channel_802_11n(msa, rx_len
						       + FCS_LEN);

	index = MAC_HDR_LEN + TIME_STAMP_LEN;

	network_info->beacon_period = get_beacon_period(msa + index);

	index += BEACON_INTERVAL_LEN + CAP_INFO_LEN;

	tim_elm = get_tim_elm(msa, rx_len + FCS_LEN, index);
	if (tim_elm)
		network_info->dtim_period = tim_elm[3];
	ies = &msa[TAG_PARAM_OFFSET];
	ies_len = rx_len - TAG_PARAM_OFFSET;

	if (ies_len > 0) {
		network_info->ies = kmemdup(ies, ies_len, GFP_KERNEL);
		if (!network_info->ies) {
			kfree(network_info);
			return -ENOMEM;
		}
	}
	network_info->ies_len = ies_len;

	*ret_network_info = network_info;

	return 0;
}