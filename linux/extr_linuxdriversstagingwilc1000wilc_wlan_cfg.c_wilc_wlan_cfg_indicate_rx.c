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
struct wilc_cfg_rsp {int seq_no; int /*<<< orphan*/  type; } ;
struct wilc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WILC_CFG_RSP ; 
 int /*<<< orphan*/  wilc_gnrl_async_info_received (struct wilc*,int*,int) ; 
 int /*<<< orphan*/  wilc_network_info_received (struct wilc*,int*,int) ; 
 int /*<<< orphan*/  wilc_scan_complete_received (struct wilc*,int*,int) ; 
 int /*<<< orphan*/  wilc_wlan_parse_info_frame (int*,int) ; 
 int /*<<< orphan*/  wilc_wlan_parse_response_frame (int*,int) ; 

int wilc_wlan_cfg_indicate_rx(struct wilc *wilc, u8 *frame, int size,
			      struct wilc_cfg_rsp *rsp)
{
	int ret = 1;
	u8 msg_type;
	u8 msg_id;

	msg_type = frame[0];
	msg_id = frame[1];      /* seq no */
	frame += 4;
	size -= 4;

	/*
	 * The valid types of response messages are
	 * 'R' (Response),
	 * 'I' (Information), and
	 * 'N' (Network Information)
	 */

	switch (msg_type) {
	case 'R':
		wilc_wlan_parse_response_frame(frame, size);
		rsp->type = WILC_CFG_RSP;
		rsp->seq_no = msg_id;
		break;

	case 'I':
		rsp->type = wilc_wlan_parse_info_frame(frame, size);
		rsp->seq_no = msg_id;
		/*call host interface info parse as well*/
		wilc_gnrl_async_info_received(wilc, frame - 4, size + 4);
		break;

	case 'N':
		wilc_network_info_received(wilc, frame - 4, size + 4);
		rsp->type = 0;
		break;

	case 'S':
		wilc_scan_complete_received(wilc, frame - 4, size + 4);
		break;

	default:
		rsp->type = 0;
		rsp->seq_no = msg_id;
		ret = 0;
		break;
	}

	return ret;
}