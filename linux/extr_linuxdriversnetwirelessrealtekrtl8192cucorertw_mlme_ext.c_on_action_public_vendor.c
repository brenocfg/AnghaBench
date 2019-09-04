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
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * rx_data; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
struct rtw_ieee80211_hdr_3addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_OUI ; 
 unsigned int _FAIL ; 
 scalar_t__ _TRUE ; 
 scalar_t__ _rtw_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned int on_action_public_p2p (union recv_frame*) ; 

unsigned int on_action_public_vendor(union recv_frame *precv_frame)
{
	unsigned int ret = _FAIL;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	uint frame_len = precv_frame->u.hdr.len;
	u8 *frame_body = pframe + sizeof(struct rtw_ieee80211_hdr_3addr);

	if (_rtw_memcmp(frame_body + 2, P2P_OUI, 4) == _TRUE) {
		ret = on_action_public_p2p(precv_frame);
	}

	return ret;
}