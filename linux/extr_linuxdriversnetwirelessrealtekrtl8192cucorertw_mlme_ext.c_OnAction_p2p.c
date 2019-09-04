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
typedef  union recv_frame {int dummy; } recv_frame ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 unsigned int _SUCCESS ; 

unsigned int OnAction_p2p(_adapter *padapter, union recv_frame *precv_frame)
{
#ifdef CONFIG_P2P
	u8 *frame_body;
	u8 category, OUI_Subtype, dialogToken=0;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	uint len = precv_frame->u.hdr.len;
	struct	wifidirect_info	*pwdinfo = &( padapter->wdinfo );
	

	DBG_871X("%s\n", __FUNCTION__);
	
	//check RA matches or not
	if (!_rtw_memcmp(myid(&(padapter->eeprompriv)), GetAddr1Ptr(pframe), ETH_ALEN))//for if1, sta/ap mode
		return _SUCCESS;

	frame_body = (unsigned char *)(pframe + sizeof(struct rtw_ieee80211_hdr_3addr));

	category = frame_body[0];
	if(category != RTW_WLAN_CATEGORY_P2P)
		return _SUCCESS;

	if ( cpu_to_be32( *( ( u32* ) ( frame_body + 1 ) ) ) != P2POUI )
		return _SUCCESS;

#ifdef CONFIG_IOCTL_CFG80211
	if(wdev_to_priv(padapter->rtw_wdev)->p2p_enabled && pwdinfo->driver_interface == DRIVER_CFG80211 )
	{
		rtw_cfg80211_rx_action_p2p(padapter, pframe, len);
		return _SUCCESS;
	}
	else
#endif //CONFIG_IOCTL_CFG80211
	{
		len -= sizeof(struct rtw_ieee80211_hdr_3addr);
		OUI_Subtype = frame_body[5];
		dialogToken = frame_body[6];

		switch(OUI_Subtype)
		{
			case P2P_NOTICE_OF_ABSENCE:
				
				break;
				
			case P2P_PRESENCE_REQUEST:

				process_p2p_presence_req(pwdinfo, pframe, len);			
				
				break;
				
			case P2P_PRESENCE_RESPONSE:
				
				break;
				
			case P2P_GO_DISC_REQUEST:
				
				break;
				
			default:
				break;
				
		}
	}
#endif //CONFIG_P2P

	return _SUCCESS;

}