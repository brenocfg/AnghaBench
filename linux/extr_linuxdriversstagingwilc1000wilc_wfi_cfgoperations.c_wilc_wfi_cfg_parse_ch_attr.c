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
 int wlan_channel ; 

__attribute__((used)) static inline void wilc_wfi_cfg_parse_ch_attr(u8 *buf, u8 ch_list_attr_idx,
					      u8 op_ch_attr_idx)
{
	int i = 0;
	int j = 0;

	if (ch_list_attr_idx) {
		u8 limit = ch_list_attr_idx + 3 + buf[ch_list_attr_idx + 1];

		for (i = ch_list_attr_idx + 3; i < limit; i++) {
			if (buf[i] == 0x51) {
				for (j = i + 2; j < ((i + 2) + buf[i + 1]); j++)
					buf[j] = wlan_channel;
				break;
			}
		}
	}

	if (op_ch_attr_idx) {
		buf[op_ch_attr_idx + 6] = 0x51;
		buf[op_ch_attr_idx + 7] = wlan_channel;
	}
}