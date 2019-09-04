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
typedef  int /*<<< orphan*/  sint ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _FAIL ; 

sint validate_recv_ctrl_frame(_adapter *padapter, union recv_frame *precv_frame)
{
#ifdef CONFIG_AP_MODE
	struct rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	struct sta_priv *pstapriv = &padapter->stapriv;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	//uint len = precv_frame->u.hdr.len;
		
	//DBG_871X("+validate_recv_ctrl_frame\n");

	if (GetFrameType(pframe) != WIFI_CTRL_TYPE)
	{		
		return _FAIL;
	}

	//receive the frames that ra(a1) is my address
	if (!_rtw_memcmp(GetAddr1Ptr(pframe), myid(&padapter->eeprompriv), ETH_ALEN))
	{
		return _FAIL;
	}

	//only handle ps-poll
	if(GetFrameSubType(pframe) == WIFI_PSPOLL)
	{
		u16 aid;
		u8 wmmps_ac=0;	
		struct sta_info *psta=NULL;
	
		aid = GetAid(pframe);
		psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));
		
		if((psta==NULL) || (psta->aid!=aid))
		{
			return _FAIL;
		}

		//for rx pkt statistics
		psta->sta_stats.rx_ctrl_pkts++;

		switch(pattrib->priority)
		{
			case 1:
			case 2:
				wmmps_ac = psta->uapsd_bk&BIT(0);
				break;
			case 4:
			case 5:
				wmmps_ac = psta->uapsd_vi&BIT(0);
				break;
			case 6:
			case 7:
				wmmps_ac = psta->uapsd_vo&BIT(0);
				break;
			case 0:
			case 3:
			default:
				wmmps_ac = psta->uapsd_be&BIT(0);
				break;	
		}

		if(wmmps_ac)
			return _FAIL;

		if(psta->state & WIFI_STA_ALIVE_CHK_STATE)
		{					
			DBG_871X("%s alive check-rx ps-poll\n", __func__);
			psta->expire_to = pstapriv->expire_to;
			psta->state ^= WIFI_STA_ALIVE_CHK_STATE;
		}	

		if((psta->state&WIFI_SLEEP_STATE) && (pstapriv->sta_dz_bitmap&BIT(psta->aid)))
		{
			_irqL irqL;	 
			_list	*xmitframe_plist, *xmitframe_phead;
			struct xmit_frame *pxmitframe=NULL;
			struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
		
			//_enter_critical_bh(&psta->sleep_q.lock, &irqL);
			_enter_critical_bh(&pxmitpriv->lock, &irqL);

			xmitframe_phead = get_list_head(&psta->sleep_q);
			xmitframe_plist = get_next(xmitframe_phead);

			if ((rtw_end_of_queue_search(xmitframe_phead, xmitframe_plist)) == _FALSE)
			{			
				pxmitframe = LIST_CONTAINOR(xmitframe_plist, struct xmit_frame, list);

				xmitframe_plist = get_next(xmitframe_plist);

				rtw_list_delete(&pxmitframe->list);

				psta->sleepq_len--;

				if(psta->sleepq_len>0)
					pxmitframe->attrib.mdata = 1;
                                else
					pxmitframe->attrib.mdata = 0;

				pxmitframe->attrib.triggered = 1;

	                        //DBG_871X("handling ps-poll, q_len=%d, tim=%x\n", psta->sleepq_len, pstapriv->tim_bitmap);

#if 0
				_exit_critical_bh(&psta->sleep_q.lock, &irqL);		
				if(rtw_hal_xmit(padapter, pxmitframe) == _TRUE)
				{		
					rtw_os_xmit_complete(padapter, pxmitframe);
				}
				_enter_critical_bh(&psta->sleep_q.lock, &irqL);	
#endif
				rtw_hal_xmitframe_enqueue(padapter, pxmitframe);

				if(psta->sleepq_len==0)
				{
					pstapriv->tim_bitmap &= ~BIT(psta->aid);

					//DBG_871X("after handling ps-poll, tim=%x\n", pstapriv->tim_bitmap);

					//upate BCN for TIM IE
					//update_BCNTIM(padapter);		
					update_beacon(padapter, _TIM_IE_, NULL, _FALSE);
				}
				
				//_exit_critical_bh(&psta->sleep_q.lock, &irqL);
				_exit_critical_bh(&pxmitpriv->lock, &irqL);
				
			}
			else
			{
				//_exit_critical_bh(&psta->sleep_q.lock, &irqL);
				_exit_critical_bh(&pxmitpriv->lock, &irqL);
			
				//DBG_871X("no buffered packets to xmit\n");
				if(pstapriv->tim_bitmap&BIT(psta->aid))
				{
					if(psta->sleepq_len==0)
					{
						DBG_871X("no buffered packets to xmit\n");

						//issue nulldata with More data bit = 0 to indicate we have no buffered packets
						issue_nulldata(padapter, psta->hwaddr, 0, 0, 0);
					}
					else
					{
						DBG_871X("error!psta->sleepq_len=%d\n", psta->sleepq_len);
						psta->sleepq_len=0;						
					}
				
					pstapriv->tim_bitmap &= ~BIT(psta->aid);					

					//upate BCN for TIM IE
					//update_BCNTIM(padapter);
					update_beacon(padapter, _TIM_IE_, NULL, _FALSE);
				}
				
			}				
			
		}
		
	}
	
#endif

	return _FAIL;

}