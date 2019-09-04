#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct recv_frame {TYPE_1__* pkt; } ;
struct ieee80211_hdr_3addr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 unsigned int _FAIL ; 
 unsigned int _SUCCESS ; 
 unsigned int rtw_action_public_decache (struct recv_frame*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int on_action_public_default(struct recv_frame *precv_frame,
					     u8 action)
{
	unsigned int ret = _FAIL;
	u8 *pframe = precv_frame->pkt->data;
	u8 *frame_body = pframe + sizeof(struct ieee80211_hdr_3addr);
	u8 token;

	token = frame_body[2];

	if (rtw_action_public_decache(precv_frame, token) == _FAIL)
		goto exit;

	ret = _SUCCESS;

exit:
	return ret;
}