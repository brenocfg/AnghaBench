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
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct xmit_priv {int free_xmitframe_cnt; int free_xmitbuf_cnt; int free_xframe_ext_cnt; int free_xmit_extbuf_cnt; int /*<<< orphan*/  hwxmit_entry; int /*<<< orphan*/  hwxmits; TYPE_1__ free_xmit_extbuf_queue; int /*<<< orphan*/ * pxmit_extbuf; int /*<<< orphan*/ * pallocated_xmit_extbuf; TYPE_1__ free_xframe_ext_queue; int /*<<< orphan*/ * xframe_ext; int /*<<< orphan*/ * xframe_ext_alloc_addr; TYPE_1__ free_xmitbuf_queue; int /*<<< orphan*/ * pxmitbuf; int /*<<< orphan*/ * pallocated_xmitbuf; TYPE_1__ pending_xmitbuf_queue; int /*<<< orphan*/  frag_len; TYPE_1__ free_xmit_queue; int /*<<< orphan*/ * pxmit_frame_buf; int /*<<< orphan*/ * pallocated_frame_buf; TYPE_1__ bm_pending; TYPE_1__ vo_pending; TYPE_1__ vi_pending; TYPE_1__ bk_pending; TYPE_1__ be_pending; int /*<<< orphan*/ * adapter; int /*<<< orphan*/  terminate_xmitthread_sema; int /*<<< orphan*/  xmit_sema; int /*<<< orphan*/  lock_sctx; int /*<<< orphan*/  lock; } ;
struct xmit_frame {int ext_tag; int /*<<< orphan*/  list; int /*<<< orphan*/ * pxmitbuf; int /*<<< orphan*/ * buf_addr; int /*<<< orphan*/ * pkt; void* frame_tag; int /*<<< orphan*/ * padapter; } ;
struct xmit_buf {int /*<<< orphan*/  list; int /*<<< orphan*/  ext_tag; int /*<<< orphan*/ * padapter; int /*<<< orphan*/ * priv_data; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ sint ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  _adapter ;
typedef  int /*<<< orphan*/  SIZE_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_FRAG_THRESHOLD ; 
 scalar_t__ MAX_XMITBUF_SZ ; 
 scalar_t__ MAX_XMIT_EXTBUF_SZ ; 
 int NR_XMITBUFF ; 
 int NR_XMITFRAME ; 
 int NR_XMIT_EXTBUFF ; 
 void* NULL_FRAMETAG ; 
 scalar_t__ N_BYTE_ALIGMENT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ XMITBUF_ALIGN_SZ ; 
 int /*<<< orphan*/  XMIT_VO_QUEUE ; 
 scalar_t__ _FAIL ; 
 int /*<<< orphan*/  _FALSE ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_xmit_c_ ; 
 int /*<<< orphan*/  _rtw_init_listhead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_init_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  _rtw_init_sema (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtw_spinlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_alloc_hwxmits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_hal_init_xmit_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_init_hwxmits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rtw_os_xmit_resource_alloc (int /*<<< orphan*/ *,struct xmit_buf*,scalar_t__) ; 
 void* rtw_zvmalloc (int) ; 

s32	_rtw_init_xmit_priv(struct xmit_priv *pxmitpriv, _adapter *padapter)
{
	int i;
	struct xmit_buf *pxmitbuf;
	struct xmit_frame *pxframe;
	sint	res=_SUCCESS;   

_func_enter_;   	

	// We don't need to memset padapter->XXX to zero, because adapter is allocated by rtw_zvmalloc().
	//_rtw_memset((unsigned char *)pxmitpriv, 0, sizeof(struct xmit_priv));
	
	_rtw_spinlock_init(&pxmitpriv->lock);
	_rtw_spinlock_init(&pxmitpriv->lock_sctx);
	_rtw_init_sema(&pxmitpriv->xmit_sema, 0);
	_rtw_init_sema(&pxmitpriv->terminate_xmitthread_sema, 0);

	/* 
	Please insert all the queue initializaiton using _rtw_init_queue below
	*/

	pxmitpriv->adapter = padapter;
	
	//for(i = 0 ; i < MAX_NUMBLKS; i++)
	//	_rtw_init_queue(&pxmitpriv->blk_strms[i]);
	
	_rtw_init_queue(&pxmitpriv->be_pending);
	_rtw_init_queue(&pxmitpriv->bk_pending);
	_rtw_init_queue(&pxmitpriv->vi_pending);
	_rtw_init_queue(&pxmitpriv->vo_pending);
	_rtw_init_queue(&pxmitpriv->bm_pending);

	//_rtw_init_queue(&pxmitpriv->legacy_dz_queue);
	//_rtw_init_queue(&pxmitpriv->apsd_queue);

	_rtw_init_queue(&pxmitpriv->free_xmit_queue);

	/*	
	Please allocate memory with the sz = (struct xmit_frame) * NR_XMITFRAME, 
	and initialize free_xmit_frame below.
	Please also apply  free_txobj to link_up all the xmit_frames...
	*/

	pxmitpriv->pallocated_frame_buf = rtw_zvmalloc(NR_XMITFRAME * sizeof(struct xmit_frame) + 4);
	
	if (pxmitpriv->pallocated_frame_buf  == NULL){
		pxmitpriv->pxmit_frame_buf =NULL;
		RT_TRACE(_module_rtl871x_xmit_c_,_drv_err_,("alloc xmit_frame fail!\n"));	
		res= _FAIL;
		goto exit;
	}
	pxmitpriv->pxmit_frame_buf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(pxmitpriv->pallocated_frame_buf), 4);
	//pxmitpriv->pxmit_frame_buf = pxmitpriv->pallocated_frame_buf + 4 -
	//						((SIZE_PTR) (pxmitpriv->pallocated_frame_buf) &3);

	pxframe = (struct xmit_frame*) pxmitpriv->pxmit_frame_buf;

	for (i = 0; i < NR_XMITFRAME; i++)
	{
		_rtw_init_listhead(&(pxframe->list));

		pxframe->padapter = padapter;
		pxframe->frame_tag = NULL_FRAMETAG;

		pxframe->pkt = NULL;		

		pxframe->buf_addr = NULL;
		pxframe->pxmitbuf = NULL;
 
		rtw_list_insert_tail(&(pxframe->list), &(pxmitpriv->free_xmit_queue.queue));

		pxframe++;
	}

	pxmitpriv->free_xmitframe_cnt = NR_XMITFRAME;

	pxmitpriv->frag_len = MAX_FRAG_THRESHOLD;


	//init xmit_buf
	_rtw_init_queue(&pxmitpriv->free_xmitbuf_queue);
	_rtw_init_queue(&pxmitpriv->pending_xmitbuf_queue);

	pxmitpriv->pallocated_xmitbuf = rtw_zvmalloc(NR_XMITBUFF * sizeof(struct xmit_buf) + 4);
	
	if (pxmitpriv->pallocated_xmitbuf  == NULL){
		RT_TRACE(_module_rtl871x_xmit_c_,_drv_err_,("alloc xmit_buf fail!\n"));
		res= _FAIL;
		goto exit;
	}

	pxmitpriv->pxmitbuf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(pxmitpriv->pallocated_xmitbuf), 4);
	//pxmitpriv->pxmitbuf = pxmitpriv->pallocated_xmitbuf + 4 -
	//						((SIZE_PTR) (pxmitpriv->pallocated_xmitbuf) &3);

	pxmitbuf = (struct xmit_buf*)pxmitpriv->pxmitbuf;

	for (i = 0; i < NR_XMITBUFF; i++)
	{
		_rtw_init_listhead(&pxmitbuf->list);

		pxmitbuf->priv_data = NULL;
		pxmitbuf->padapter = padapter;
		pxmitbuf->ext_tag = _FALSE;

/*
		pxmitbuf->pallocated_buf = rtw_zmalloc(MAX_XMITBUF_SZ + XMITBUF_ALIGN_SZ);
		if (pxmitbuf->pallocated_buf == NULL)
		{
			res = _FAIL;
			goto exit;
		}

		pxmitbuf->pbuf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(pxmitbuf->pallocated_buf), XMITBUF_ALIGN_SZ);
		//pxmitbuf->pbuf = pxmitbuf->pallocated_buf + XMITBUF_ALIGN_SZ -((SIZE_PTR) (pxmitbuf->pallocated_buf) &(XMITBUF_ALIGN_SZ-1));
*/

		if((res=rtw_os_xmit_resource_alloc(padapter, pxmitbuf,(MAX_XMITBUF_SZ + XMITBUF_ALIGN_SZ))) == _FAIL) {
			res= _FAIL;
			goto exit;
		}

#ifdef CONFIG_SDIO_HCI
		pxmitbuf->phead = pxmitbuf->pbuf;
		pxmitbuf->pend = pxmitbuf->pbuf + MAX_XMITBUF_SZ;
		pxmitbuf->len = 0;
		pxmitbuf->pdata = pxmitbuf->ptail = pxmitbuf->phead;
#endif

		pxmitbuf->flags = XMIT_VO_QUEUE;
		
		rtw_list_insert_tail(&pxmitbuf->list, &(pxmitpriv->free_xmitbuf_queue.queue));
		#ifdef DBG_XMIT_BUF
		pxmitbuf->no=i;
		#endif

		pxmitbuf++;
		
	}

	pxmitpriv->free_xmitbuf_cnt = NR_XMITBUFF;

	/* init xframe_ext queue,  the same count as extbuf  */
	_rtw_init_queue(&pxmitpriv->free_xframe_ext_queue);
	
	pxmitpriv->xframe_ext_alloc_addr = rtw_zvmalloc(NR_XMIT_EXTBUFF * sizeof(struct xmit_frame) + 4);
	
	if (pxmitpriv->xframe_ext_alloc_addr  == NULL){
		pxmitpriv->xframe_ext = NULL;
		RT_TRACE(_module_rtl871x_xmit_c_,_drv_err_,("alloc xframe_ext fail!\n"));	
		res= _FAIL;
		goto exit;
	}
	pxmitpriv->xframe_ext = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(pxmitpriv->xframe_ext_alloc_addr), 4);
	pxframe = (struct xmit_frame*)pxmitpriv->xframe_ext;

	for (i = 0; i < NR_XMIT_EXTBUFF; i++) {
		_rtw_init_listhead(&(pxframe->list));

		pxframe->padapter = padapter;
		pxframe->frame_tag = NULL_FRAMETAG;

		pxframe->pkt = NULL;		

		pxframe->buf_addr = NULL;
		pxframe->pxmitbuf = NULL;
		
		pxframe->ext_tag = 1;
 
		rtw_list_insert_tail(&(pxframe->list), &(pxmitpriv->free_xframe_ext_queue.queue));

		pxframe++;
	}
	pxmitpriv->free_xframe_ext_cnt = NR_XMIT_EXTBUFF;

	// Init xmit extension buff
	_rtw_init_queue(&pxmitpriv->free_xmit_extbuf_queue);

	pxmitpriv->pallocated_xmit_extbuf = rtw_zvmalloc(NR_XMIT_EXTBUFF * sizeof(struct xmit_buf) + 4);
	
	if (pxmitpriv->pallocated_xmit_extbuf  == NULL){
		RT_TRACE(_module_rtl871x_xmit_c_,_drv_err_,("alloc xmit_extbuf fail!\n"));
		res= _FAIL;
		goto exit;
	}

	pxmitpriv->pxmit_extbuf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(pxmitpriv->pallocated_xmit_extbuf), 4);

	pxmitbuf = (struct xmit_buf*)pxmitpriv->pxmit_extbuf;

	for (i = 0; i < NR_XMIT_EXTBUFF; i++)
	{
		_rtw_init_listhead(&pxmitbuf->list);

		pxmitbuf->priv_data = NULL;
		pxmitbuf->padapter = padapter;
		pxmitbuf->ext_tag = _TRUE;

/*
		pxmitbuf->pallocated_buf = rtw_zmalloc(MAX_XMIT_EXTBUF_SZ);
		if (pxmitbuf->pallocated_buf == NULL)
		{
			res = _FAIL;
			goto exit;
		}

		pxmitbuf->pbuf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(pxmitbuf->pallocated_buf), 4);
*/		

		if((res=rtw_os_xmit_resource_alloc(padapter, pxmitbuf,MAX_XMIT_EXTBUF_SZ + XMITBUF_ALIGN_SZ)) == _FAIL) {
			res= _FAIL;
			goto exit;
		}
		
#ifdef CONFIG_SDIO_HCI
		pxmitbuf->phead = pxmitbuf->pbuf;
		pxmitbuf->pend = pxmitbuf->pbuf + MAX_XMIT_EXTBUF_SZ;
		pxmitbuf->len = 0;
		pxmitbuf->pdata = pxmitbuf->ptail = pxmitbuf->phead;
#endif

		rtw_list_insert_tail(&pxmitbuf->list, &(pxmitpriv->free_xmit_extbuf_queue.queue));
		#ifdef DBG_XMIT_BUF
		pxmitbuf->no=i;
		#endif
		pxmitbuf++;
		
	}

	pxmitpriv->free_xmit_extbuf_cnt = NR_XMIT_EXTBUFF;

	rtw_alloc_hwxmits(padapter);
	rtw_init_hwxmits(pxmitpriv->hwxmits, pxmitpriv->hwxmit_entry);

#ifdef CONFIG_USB_HCI
	pxmitpriv->txirp_cnt=1;

	_rtw_init_sema(&(pxmitpriv->tx_retevt), 0);

	//per AC pending irp
	pxmitpriv->beq_cnt = 0;
	pxmitpriv->bkq_cnt = 0;
	pxmitpriv->viq_cnt = 0;
	pxmitpriv->voq_cnt = 0;
#endif


#ifdef CONFIG_XMIT_ACK
	pxmitpriv->ack_tx = _FALSE;
	_rtw_mutex_init(&pxmitpriv->ack_tx_mutex);
	rtw_sctx_init(&pxmitpriv->ack_tx_ops, 0);	
#endif

	rtw_hal_init_xmit_priv(padapter);

exit:

_func_exit_;	

	return res;
}