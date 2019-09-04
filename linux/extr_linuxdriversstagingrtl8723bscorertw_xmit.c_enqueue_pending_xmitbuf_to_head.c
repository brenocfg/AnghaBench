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
struct xmit_priv {struct __queue pending_xmitbuf_queue; } ;
struct xmit_buf {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_list_head (struct __queue*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void enqueue_pending_xmitbuf_to_head(
	struct xmit_priv *pxmitpriv,
	struct xmit_buf *pxmitbuf)
{
	struct __queue *pqueue;

	pqueue = &pxmitpriv->pending_xmitbuf_queue;

	spin_lock_bh(&pqueue->lock);
	list_del_init(&pxmitbuf->list);
	list_add(&pxmitbuf->list, get_list_head(pqueue));
	spin_unlock_bh(&pqueue->lock);
}