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
struct xmit_priv {int /*<<< orphan*/  lock; } ;
struct pkt_attrib {int dummy; } ;
struct xmit_frame {struct pkt_attrib attrib; } ;
struct xmit_buf {int dummy; } ;
struct _adapter {struct xmit_priv xmitpriv; } ;

/* Variables and functions */
 struct xmit_buf* r8712_alloc_xmitbuf (struct xmit_priv*) ; 
 int /*<<< orphan*/  r8712_do_queue_select (struct _adapter*,struct pkt_attrib*) ; 
 scalar_t__ r8712_txframes_sta_ac_pending (struct _adapter*,struct pkt_attrib*) ; 
 int /*<<< orphan*/  r8712_xmit_direct (struct _adapter*,struct xmit_frame*) ; 
 int /*<<< orphan*/  r8712_xmit_enqueue (struct _adapter*,struct xmit_frame*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xmitframe_xmitbuf_attach (struct xmit_frame*,struct xmit_buf*) ; 

int r8712_pre_xmit(struct _adapter *padapter, struct xmit_frame *pxmitframe)
{
	unsigned long irqL;
	int ret;
	struct xmit_buf *pxmitbuf = NULL;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct pkt_attrib *pattrib = &pxmitframe->attrib;

	r8712_do_queue_select(padapter, pattrib);
	spin_lock_irqsave(&pxmitpriv->lock, irqL);
	if (r8712_txframes_sta_ac_pending(padapter, pattrib) > 0) {
		ret = false;
		r8712_xmit_enqueue(padapter, pxmitframe);
		spin_unlock_irqrestore(&pxmitpriv->lock, irqL);
		return ret;
	}
	pxmitbuf = r8712_alloc_xmitbuf(pxmitpriv);
	if (pxmitbuf == NULL) { /*enqueue packet*/
		ret = false;
		r8712_xmit_enqueue(padapter, pxmitframe);
		spin_unlock_irqrestore(&pxmitpriv->lock, irqL);
	} else { /*dump packet directly*/
		spin_unlock_irqrestore(&pxmitpriv->lock, irqL);
		ret = true;
		xmitframe_xmitbuf_attach(pxmitframe, pxmitbuf);
		r8712_xmit_direct(padapter, pxmitframe);
	}
	return ret;
}