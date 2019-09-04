#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ mfrag; scalar_t__ frag_num; scalar_t__ privacy; scalar_t__* ta; } ;
struct recv_frame_hdr {TYPE_3__ attrib; int /*<<< orphan*/  list; int /*<<< orphan*/  rx_data; } ;
struct TYPE_13__ {struct recv_frame_hdr hdr; } ;
union recv_frame {TYPE_4__ u; } ;
typedef  scalar_t__ u8 ;
struct sta_priv {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  defrag_q; } ;
struct sta_info {TYPE_2__ sta_recvpriv; } ;
typedef  int /*<<< orphan*/  _queue ;
typedef  int /*<<< orphan*/  _list ;
struct TYPE_10__ {int /*<<< orphan*/  free_recv_queue; } ;
struct TYPE_14__ {TYPE_1__ recvpriv; struct sta_priv stapriv; } ;
typedef  TYPE_5__* PADAPTER ;

/* Variables and functions */
 scalar_t__ GetFrameType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ WIFI_DATA_TYPE ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _FALSE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 scalar_t__ _rtw_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_list_head (int /*<<< orphan*/ *) ; 
 scalar_t__ recvframe_chkmic (TYPE_5__*,union recv_frame*) ; 
 union recv_frame* recvframe_defrag (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_free_recvframe (union recv_frame*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_free_recvframe_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sta_info* rtw_get_bcmc_stainfo (TYPE_5__*) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,scalar_t__*) ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

union recv_frame* recvframe_chk_defrag(PADAPTER padapter, union recv_frame *precv_frame)
{
	u8	ismfrag;
	u8	fragnum;
	u8	*psta_addr;
	struct recv_frame_hdr *pfhdr;
	struct sta_info *psta;
	struct sta_priv *pstapriv;
	_list *phead;
	union recv_frame *prtnframe = NULL;
	_queue *pfree_recv_queue, *pdefrag_q;

_func_enter_;

	pstapriv = &padapter->stapriv;

	pfhdr = &precv_frame->u.hdr;

	pfree_recv_queue = &padapter->recvpriv.free_recv_queue;

	//need to define struct of wlan header frame ctrl
	ismfrag = pfhdr->attrib.mfrag;
	fragnum = pfhdr->attrib.frag_num;

	psta_addr = pfhdr->attrib.ta;
	psta = rtw_get_stainfo(pstapriv, psta_addr);
	if (psta == NULL)
	{
		u8 type = GetFrameType(pfhdr->rx_data);
		if (type != WIFI_DATA_TYPE) {
			psta = rtw_get_bcmc_stainfo(padapter);
			pdefrag_q = &psta->sta_recvpriv.defrag_q;
		} else
			pdefrag_q = NULL;
	}
	else
		pdefrag_q = &psta->sta_recvpriv.defrag_q;

	if ((ismfrag==0) && (fragnum==0))
	{
		prtnframe = precv_frame;//isn't a fragment frame
	}

	if (ismfrag==1)
	{
		//0~(n-1) fragment frame
		//enqueue to defraf_g
		if(pdefrag_q != NULL)
		{
			if(fragnum==0)
			{
				//the first fragment
				if(_rtw_queue_empty(pdefrag_q) == _FALSE)
				{
					//free current defrag_q
					rtw_free_recvframe_queue(pdefrag_q, pfree_recv_queue);
				}
			}


			//Then enqueue the 0~(n-1) fragment into the defrag_q

			//_rtw_spinlock(&pdefrag_q->lock);
			phead = get_list_head(pdefrag_q);
			rtw_list_insert_tail(&pfhdr->list, phead);
			//_rtw_spinunlock(&pdefrag_q->lock);

			RT_TRACE(_module_rtl871x_recv_c_,_drv_info_,("Enqueuq: ismfrag = %d, fragnum= %d\n", ismfrag,fragnum));

			prtnframe=NULL;

		}
		else
		{
			//can't find this ta's defrag_queue, so free this recv_frame
			rtw_free_recvframe(precv_frame, pfree_recv_queue);
			prtnframe=NULL;
			RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("Free because pdefrag_q ==NULL: ismfrag = %d, fragnum= %d\n", ismfrag, fragnum));
		}

	}

	if((ismfrag==0)&&(fragnum!=0))
	{
		//the last fragment frame
		//enqueue the last fragment
		if(pdefrag_q != NULL)
		{
			//_rtw_spinlock(&pdefrag_q->lock);
			phead = get_list_head(pdefrag_q);
			rtw_list_insert_tail(&pfhdr->list,phead);
			//_rtw_spinunlock(&pdefrag_q->lock);

			//call recvframe_defrag to defrag
			RT_TRACE(_module_rtl871x_recv_c_,_drv_info_,("defrag: ismfrag = %d, fragnum= %d\n", ismfrag, fragnum));
			precv_frame = recvframe_defrag(padapter, pdefrag_q);
			prtnframe=precv_frame;

		}
		else
		{
			//can't find this ta's defrag_queue, so free this recv_frame
			rtw_free_recvframe(precv_frame, pfree_recv_queue);
			prtnframe=NULL;
			RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("Free because pdefrag_q ==NULL: ismfrag = %d, fragnum= %d\n", ismfrag,fragnum));
		}

	}


	if((prtnframe!=NULL)&&(prtnframe->u.hdr.attrib.privacy))
	{
		//after defrag we must check tkip mic code
		if(recvframe_chkmic(padapter,  prtnframe)==_FAIL)
		{
			RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("recvframe_chkmic(padapter,  prtnframe)==_FAIL\n"));
			rtw_free_recvframe(prtnframe,pfree_recv_queue);
			prtnframe=NULL;
		}
	}

_func_exit_;

	return prtnframe;

}