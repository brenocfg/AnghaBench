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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ GET_RX_BUFFER_DESC_FS (scalar_t__*) ; 
 scalar_t__ GET_RX_BUFFER_DESC_LS (scalar_t__*) ; 
 scalar_t__ GET_RX_BUFFER_DESC_TOTAL_LENGTH (scalar_t__*) ; 

void rtl92ee_rx_check_dma_ok(struct ieee80211_hw *hw, u8 *header_desc,
			     u8 queue_index)
{
	u8 first_seg = 0;
	u8 last_seg = 0;
	u16 total_len = 0;
	u16 read_cnt = 0;

	if (header_desc == NULL)
		return;

	total_len = (u16)GET_RX_BUFFER_DESC_TOTAL_LENGTH(header_desc);

	first_seg = (u8)GET_RX_BUFFER_DESC_FS(header_desc);

	last_seg = (u8)GET_RX_BUFFER_DESC_LS(header_desc);

	while (total_len == 0 && first_seg == 0 && last_seg == 0) {
		read_cnt++;
		total_len = (u16)GET_RX_BUFFER_DESC_TOTAL_LENGTH(header_desc);
		first_seg = (u8)GET_RX_BUFFER_DESC_FS(header_desc);
		last_seg = (u8)GET_RX_BUFFER_DESC_LS(header_desc);

		if (read_cnt > 20)
			break;
	}
}