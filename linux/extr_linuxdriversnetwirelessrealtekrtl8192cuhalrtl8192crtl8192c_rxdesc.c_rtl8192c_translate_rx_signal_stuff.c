#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int /*<<< orphan*/  crc_err; int /*<<< orphan*/  icv_err; scalar_t__ physt; } ;
struct TYPE_9__ {struct sta_info* psta; int /*<<< orphan*/  rx_data; TYPE_5__* adapter; struct rx_pkt_attrib attrib; } ;
struct TYPE_10__ {TYPE_3__ hdr; } ;
union recv_frame {TYPE_4__ u; } ;
typedef  int u8 ;
struct sta_priv {int dummy; } ;
struct sta_info {int dummy; } ;
struct phy_stat {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  network; } ;
struct TYPE_8__ {TYPE_1__ mlmext_info; } ;
struct TYPE_11__ {struct sta_priv stapriv; int /*<<< orphan*/  mlmepriv; int /*<<< orphan*/  eeprompriv; TYPE_2__ mlmeextpriv; } ;
typedef  TYPE_5__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ GetFrameSubType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsFrameTypeCtrl (int /*<<< orphan*/ ) ; 
 int WIFI_ADHOC_MASTER_STATE ; 
 int WIFI_ADHOC_STATE ; 
 int WIFI_AP_STATE ; 
 scalar_t__ WIFI_BEACON ; 
 int _FALSE ; 
 scalar_t__ _TRUE ; 
 scalar_t__ _rtw_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ check_fwstate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_da (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_hdr_bssid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_my_bssid (int /*<<< orphan*/ *) ; 
 int* get_sa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_phy_info (TYPE_5__*,union recv_frame*) ; 
 int /*<<< orphan*/  query_rx_phy_status (union recv_frame*,struct phy_stat*) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int*) ; 

void rtl8192c_translate_rx_signal_stuff(union recv_frame *precvframe, struct phy_stat *pphy_info)
{
	struct rx_pkt_attrib	*pattrib = &precvframe->u.hdr.attrib;
	_adapter				*padapter = precvframe->u.hdr.adapter;
	u8	bPacketMatchBSSID =_FALSE;
	u8	bPacketToSelf = _FALSE;
	u8	bPacketBeacon = _FALSE;

	if((pattrib->physt) && (pphy_info != NULL))
	{
		bPacketMatchBSSID = ((!IsFrameTypeCtrl(precvframe->u.hdr.rx_data)) && !(pattrib->icv_err) && !(pattrib->crc_err) &&
			_rtw_memcmp(get_hdr_bssid(precvframe->u.hdr.rx_data), get_my_bssid(&padapter->mlmeextpriv.mlmext_info.network), ETH_ALEN));
			

		bPacketToSelf = bPacketMatchBSSID &&  (_rtw_memcmp(get_da(precvframe->u.hdr.rx_data), myid(&padapter->eeprompriv), ETH_ALEN));

		bPacketBeacon =bPacketMatchBSSID && (GetFrameSubType(precvframe->u.hdr.rx_data) ==  WIFI_BEACON);

		query_rx_phy_status(precvframe, pphy_info);

		precvframe->u.hdr.psta = NULL;
		if(bPacketMatchBSSID && check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE) == _TRUE)
		{
			u8 *sa;
			struct sta_info *psta=NULL;
			struct sta_priv *pstapriv = &padapter->stapriv;
			
			sa = get_sa(precvframe->u.hdr.rx_data);

			psta = rtw_get_stainfo(pstapriv, sa);
			if(psta)
			{
				precvframe->u.hdr.psta = psta;
				process_phy_info(padapter, precvframe);
			}
		}
		else if(bPacketToSelf || bPacketBeacon)
		{
			if(check_fwstate(&padapter->mlmepriv, WIFI_ADHOC_STATE|WIFI_ADHOC_MASTER_STATE) == _TRUE)
			{
				u8 *sa;
				struct sta_info *psta=NULL;
				struct sta_priv *pstapriv = &padapter->stapriv;
			
				sa = get_sa(precvframe->u.hdr.rx_data);

				psta = rtw_get_stainfo(pstapriv, sa);
				if(psta)
				{
					precvframe->u.hdr.psta = psta;
				}				
			}
					
			process_phy_info(padapter, precvframe);
		}
	}
}