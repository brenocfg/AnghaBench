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
struct TYPE_3__ {int /*<<< orphan*/ * adapter; int /*<<< orphan*/  len; int /*<<< orphan*/ * rx_data; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
struct rtw_ieee80211_hdr_3addr {int dummy; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 unsigned int _FAIL ; 
 unsigned int _SUCCESS ; 
 unsigned int rtw_action_public_decache (union recv_frame*,int /*<<< orphan*/ ) ; 

unsigned int on_action_public_default(union recv_frame *precv_frame, u8 action)
{
	unsigned int ret = _FAIL;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	uint frame_len = precv_frame->u.hdr.len;
	u8 *frame_body = pframe + sizeof(struct rtw_ieee80211_hdr_3addr);
	u8 token;
	_adapter *adapter = precv_frame->u.hdr.adapter;
	int cnt = 0;
	char msg[64];

	token = frame_body[2];

	if (rtw_action_public_decache(precv_frame, token) == _FAIL)
		goto exit;

	#ifdef CONFIG_IOCTL_CFG80211
	cnt += sprintf((msg+cnt), "%s(token:%u)", action_public_str(action), token);
	rtw_cfg80211_rx_action(adapter, pframe, frame_len, msg);
	#endif

	ret = _SUCCESS;
	
exit:
	return ret;
}