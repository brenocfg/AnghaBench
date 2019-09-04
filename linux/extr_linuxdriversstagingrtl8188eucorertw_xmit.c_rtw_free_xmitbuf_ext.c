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
struct __queue {int /*<<< orphan*/  lock; } ;
struct xmit_priv {int /*<<< orphan*/  free_xmit_extbuf_cnt; struct __queue free_xmit_extbuf_queue; } ;
struct xmit_buf {int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  get_list_head (struct __queue*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

s32 rtw_free_xmitbuf_ext(struct xmit_priv *pxmitpriv, struct xmit_buf *pxmitbuf)
{
	unsigned long irql;
	struct __queue *pfree_queue = &pxmitpriv->free_xmit_extbuf_queue;

	if (!pxmitbuf)
		return _FAIL;

	spin_lock_irqsave(&pfree_queue->lock, irql);

	list_del_init(&pxmitbuf->list);

	list_add_tail(&pxmitbuf->list, get_list_head(pfree_queue));
	pxmitpriv->free_xmit_extbuf_cnt++;

	spin_unlock_irqrestore(&pfree_queue->lock, irql);

	return _SUCCESS;
}