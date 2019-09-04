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
struct xmit_priv {int /*<<< orphan*/  hwxmit_entry; struct hw_xmit* hwxmits; } ;
struct TYPE_2__ {int priority; } ;
struct xmit_frame {int frame_tag; int /*<<< orphan*/  pkt; TYPE_1__ attrib; int /*<<< orphan*/  buf_addr; struct xmit_buf* pxmitbuf; } ;
struct xmit_buf {struct xmit_frame* priv_data; int /*<<< orphan*/  pbuf; } ;
struct hw_xmit {int dummy; } ;
typedef  int /*<<< orphan*/  sint ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int DATA_FRAMETAG ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FALSE ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _TRUE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_xmit_c_ ; 
 struct xmit_buf* rtw_alloc_xmitbuf (struct xmit_priv*) ; 
 struct xmit_frame* rtw_dequeue_xframe (struct xmit_priv*,struct hw_xmit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_dump_xframe (int /*<<< orphan*/ *,struct xmit_frame*) ; 
 int /*<<< orphan*/  rtw_free_xmitbuf (struct xmit_priv*,struct xmit_buf*) ; 
 int /*<<< orphan*/  rtw_free_xmitframe (struct xmit_priv*,struct xmit_frame*) ; 
 int /*<<< orphan*/  rtw_os_xmit_complete (int /*<<< orphan*/ *,struct xmit_frame*) ; 
 int rtw_xmitframe_coalesce (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct xmit_frame*) ; 

s32 rtl8192cu_xmitframe_complete(_adapter *padapter, struct xmit_priv *pxmitpriv, struct xmit_buf *pxmitbuf)
{		

	struct hw_xmit *phwxmits;
	sint hwentry;
	struct xmit_frame *pxmitframe=NULL;	
	int res=_SUCCESS, xcnt = 0;

	phwxmits = pxmitpriv->hwxmits;
	hwentry = pxmitpriv->hwxmit_entry;

	RT_TRACE(_module_rtl871x_xmit_c_,_drv_info_,("xmitframe_complete()\n"));

	if(pxmitbuf==NULL)
	{
		pxmitbuf = rtw_alloc_xmitbuf(pxmitpriv);		
		if(!pxmitbuf)
		{
			return _FALSE;
		}			
	}	


	do
	{		
		pxmitframe =  rtw_dequeue_xframe(pxmitpriv, phwxmits, hwentry);
		
		if(pxmitframe)
		{
			pxmitframe->pxmitbuf = pxmitbuf;				

			pxmitframe->buf_addr = pxmitbuf->pbuf;

			pxmitbuf->priv_data = pxmitframe;	

			if((pxmitframe->frame_tag&0x0f) == DATA_FRAMETAG)
			{	
				if(pxmitframe->attrib.priority<=15)//TID0~15
				{
					res = rtw_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);
				}	
							
				rtw_os_xmit_complete(padapter, pxmitframe);//always return ndis_packet after rtw_xmitframe_coalesce 			
			}

				
			RT_TRACE(_module_rtl871x_xmit_c_,_drv_info_,("xmitframe_complete(): rtw_dump_xframe\n"));

			
			if(res == _SUCCESS)
			{
				rtw_dump_xframe(padapter, pxmitframe);
			}
			else
			{
				rtw_free_xmitbuf(pxmitpriv, pxmitbuf);
				rtw_free_xmitframe(pxmitpriv, pxmitframe);	
			}
	 			 		
			xcnt++;
			
		}
		else
		{			
			rtw_free_xmitbuf(pxmitpriv, pxmitbuf);
			return _FALSE;
		}

		break;
		
	}while(0/*xcnt < (NR_XMITFRAME >> 3)*/);

	return _TRUE;
	
}