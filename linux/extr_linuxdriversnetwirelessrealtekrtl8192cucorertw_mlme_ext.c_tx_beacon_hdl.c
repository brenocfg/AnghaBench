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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int /*<<< orphan*/  H2C_PARAMETERS_ERROR ; 
 int /*<<< orphan*/  H2C_SUCCESS ; 
 scalar_t__ _FAIL ; 
 scalar_t__ send_beacon (int /*<<< orphan*/ *) ; 

u8 tx_beacon_hdl(_adapter *padapter, unsigned char *pbuf)
{
	if(send_beacon(padapter)==_FAIL)
	{
		DBG_871X("issue_beacon, fail!\n");
		return H2C_PARAMETERS_ERROR;
	}
#ifdef CONFIG_AP_MODE
	else //tx bc/mc frames after update TIM 
	{	
		_irqL irqL;
		struct sta_info *psta_bmc;
		_list	*xmitframe_plist, *xmitframe_phead;
		struct xmit_frame *pxmitframe=NULL;
		struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
		struct sta_priv  *pstapriv = &padapter->stapriv;
		
		//for BC/MC Frames
		psta_bmc = rtw_get_bcmc_stainfo(padapter);
		if(!psta_bmc)
			return H2C_SUCCESS;
	
		if((pstapriv->tim_bitmap&BIT(0)) && (psta_bmc->sleepq_len>0))
		{				
#ifndef CONFIG_PCI_HCI
			rtw_msleep_os(10);// 10ms, ATIM(HIQ) Windows
#endif
			//_enter_critical_bh(&psta_bmc->sleep_q.lock, &irqL);
			_enter_critical_bh(&pxmitpriv->lock, &irqL);

			xmitframe_phead = get_list_head(&psta_bmc->sleep_q);
			xmitframe_plist = get_next(xmitframe_phead);

			while ((rtw_end_of_queue_search(xmitframe_phead, xmitframe_plist)) == _FALSE)
			{			
				pxmitframe = LIST_CONTAINOR(xmitframe_plist, struct xmit_frame, list);

				xmitframe_plist = get_next(xmitframe_plist);

				rtw_list_delete(&pxmitframe->list);

				psta_bmc->sleepq_len--;
				if(psta_bmc->sleepq_len>0)
					pxmitframe->attrib.mdata = 1;
				else
					pxmitframe->attrib.mdata = 0;

				pxmitframe->attrib.triggered=1;

				pxmitframe->attrib.qsel = 0x11;//HIQ

#if 0
				_exit_critical_bh(&psta_bmc->sleep_q.lock, &irqL);
				if(rtw_hal_xmit(padapter, pxmitframe) == _TRUE)
				{		
					rtw_os_xmit_complete(padapter, pxmitframe);
				}
				_enter_critical_bh(&psta_bmc->sleep_q.lock, &irqL);

#endif
				rtw_hal_xmitframe_enqueue(padapter, pxmitframe);

				//pstapriv->tim_bitmap &= ~BIT(0);				
		
			}	
	
			//_exit_critical_bh(&psta_bmc->sleep_q.lock, &irqL);
	               _exit_critical_bh(&pxmitpriv->lock, &irqL);

		}

	}
#endif

	return H2C_SUCCESS;
	
}