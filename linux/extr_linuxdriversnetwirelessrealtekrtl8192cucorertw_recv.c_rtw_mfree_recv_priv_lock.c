#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct recv_priv {TYPE_3__ free_recv_buf_queue; TYPE_2__ recv_pending_queue; TYPE_1__ free_recv_queue; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtw_spinlock_free (int /*<<< orphan*/ *) ; 

void rtw_mfree_recv_priv_lock(struct recv_priv *precvpriv)
{
	_rtw_spinlock_free(&precvpriv->lock);
#ifdef CONFIG_RECV_THREAD_MODE	
	_rtw_free_sema(&precvpriv->recv_sema);
	_rtw_free_sema(&precvpriv->terminate_recvthread_sema);
#endif

	_rtw_spinlock_free(&precvpriv->free_recv_queue.lock);
	_rtw_spinlock_free(&precvpriv->recv_pending_queue.lock);

	_rtw_spinlock_free(&precvpriv->free_recv_buf_queue.lock);

#ifdef CONFIG_USE_USB_BUFFER_ALLOC_RX
	_rtw_spinlock_free(&precvpriv->recv_buf_pending_queue.lock);
#endif	// CONFIG_USE_USB_BUFFER_ALLOC_RX
}