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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct xmit_priv {scalar_t__ pallocated_xmit_extbuf; scalar_t__ pxmit_extbuf; TYPE_2__ free_xmit_extbuf_queue; TYPE_1__ free_xframe_ext_queue; scalar_t__ xframe_ext_alloc_addr; scalar_t__ xframe_ext; scalar_t__ pallocated_xmitbuf; scalar_t__ pallocated_frame_buf; int /*<<< orphan*/ * pxmit_frame_buf; scalar_t__ pxmitbuf; int /*<<< orphan*/ * adapter; } ;
struct xmit_frame {int dummy; } ;
struct xmit_buf {int dummy; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 scalar_t__ MAX_XMITBUF_SZ ; 
 scalar_t__ MAX_XMIT_EXTBUF_SZ ; 
 int NR_XMITBUFF ; 
 int NR_XMITFRAME ; 
 int NR_XMIT_EXTBUFF ; 
 scalar_t__ XMITBUF_ALIGN_SZ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_spinlock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_free_hwxmits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_hal_free_xmit_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_mfree_xmit_priv_lock (struct xmit_priv*) ; 
 int /*<<< orphan*/  rtw_os_xmit_complete (int /*<<< orphan*/ *,struct xmit_frame*) ; 
 int /*<<< orphan*/  rtw_os_xmit_resource_free (int /*<<< orphan*/ *,struct xmit_buf*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_vmfree (scalar_t__,int) ; 

void _rtw_free_xmit_priv (struct xmit_priv *pxmitpriv)
{
       int i;
      _adapter *padapter = pxmitpriv->adapter;
	struct xmit_frame	*pxmitframe = (struct xmit_frame*) pxmitpriv->pxmit_frame_buf;
	struct xmit_buf *pxmitbuf = (struct xmit_buf *)pxmitpriv->pxmitbuf;

 _func_enter_;   

	rtw_hal_free_xmit_priv(padapter);
 
	rtw_mfree_xmit_priv_lock(pxmitpriv);
 
 	if(pxmitpriv->pxmit_frame_buf==NULL)
		goto out;
	
	for(i=0; i<NR_XMITFRAME; i++)
	{	
		rtw_os_xmit_complete(padapter, pxmitframe);

		pxmitframe++;
	}		
	
	for(i=0; i<NR_XMITBUFF; i++)
	{
		rtw_os_xmit_resource_free(padapter, pxmitbuf,(MAX_XMITBUF_SZ + XMITBUF_ALIGN_SZ));

		//if(pxmitbuf->pallocated_buf)
		//	rtw_mfree(pxmitbuf->pallocated_buf, MAX_XMITBUF_SZ + XMITBUF_ALIGN_SZ);
		
		pxmitbuf++;
	}

	if(pxmitpriv->pallocated_frame_buf) {
		rtw_vmfree(pxmitpriv->pallocated_frame_buf, NR_XMITFRAME * sizeof(struct xmit_frame) + 4);
	}
	

	if(pxmitpriv->pallocated_xmitbuf) {
		rtw_vmfree(pxmitpriv->pallocated_xmitbuf, NR_XMITBUFF * sizeof(struct xmit_buf) + 4);
	}

	/* free xframe_ext queue,  the same count as extbuf  */
	if ((pxmitframe = (struct xmit_frame*)pxmitpriv->xframe_ext)) {
		for (i=0; i<NR_XMIT_EXTBUFF; i++) {
			rtw_os_xmit_complete(padapter, pxmitframe);
			pxmitframe++;
		}
	}
	if (pxmitpriv->xframe_ext_alloc_addr)
		rtw_vmfree(pxmitpriv->xframe_ext_alloc_addr, NR_XMIT_EXTBUFF * sizeof(struct xmit_frame) + 4);
	_rtw_spinlock_free(&pxmitpriv->free_xframe_ext_queue.lock);

	// free xmit extension buff
	_rtw_spinlock_free(&pxmitpriv->free_xmit_extbuf_queue.lock);

	pxmitbuf = (struct xmit_buf *)pxmitpriv->pxmit_extbuf;
	for(i=0; i<NR_XMIT_EXTBUFF; i++)
	{
		rtw_os_xmit_resource_free(padapter, pxmitbuf,(MAX_XMIT_EXTBUF_SZ + XMITBUF_ALIGN_SZ));

		//if(pxmitbuf->pallocated_buf)
		//	rtw_mfree(pxmitbuf->pallocated_buf, MAX_XMIT_EXTBUF_SZ);
		
		pxmitbuf++;
	}

	if(pxmitpriv->pallocated_xmit_extbuf) {
		rtw_vmfree(pxmitpriv->pallocated_xmit_extbuf, NR_XMIT_EXTBUFF * sizeof(struct xmit_buf) + 4);	
	}

	rtw_free_hwxmits(padapter);

#ifdef CONFIG_XMIT_ACK	
	_rtw_mutex_free(&pxmitpriv->ack_tx_mutex);	
#endif	

out:	

_func_exit_;		

}