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
struct TYPE_3__ {scalar_t__* rx_data; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  scalar_t__ u8 ;
struct ieee80211_hdr_3addr {int dummy; } ;
struct adapter {int /*<<< orphan*/  eeprompriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GetAddr1Ptr (scalar_t__*) ; 
#define  RTW_WLAN_ACTION_HT_COMPRESS_BEAMFORMING 128 
 scalar_t__ RTW_WLAN_CATEGORY_HT ; 
 unsigned int _SUCCESS ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myid (int /*<<< orphan*/ *) ; 

unsigned int OnAction_ht(struct adapter *padapter, union recv_frame *precv_frame)
{
	u8 *pframe = precv_frame->u.hdr.rx_data;
	u8 *frame_body = pframe + sizeof(struct ieee80211_hdr_3addr);
	u8 category, action;

	/* check RA matches or not */
	if (memcmp(myid(&(padapter->eeprompriv)), GetAddr1Ptr(pframe), ETH_ALEN))
		goto exit;

	category = frame_body[0];
	if (category != RTW_WLAN_CATEGORY_HT)
		goto exit;

	action = frame_body[1];
	switch (action) {
	case RTW_WLAN_ACTION_HT_COMPRESS_BEAMFORMING:
		break;
	default:
		break;
	}

exit:

	return _SUCCESS;
}