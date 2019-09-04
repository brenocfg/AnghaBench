#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  lock; } ;
struct TYPE_15__ {int /*<<< orphan*/  lock; } ;
struct TYPE_14__ {int /*<<< orphan*/  lock; } ;
struct TYPE_13__ {int /*<<< orphan*/  lock; } ;
struct TYPE_12__ {int /*<<< orphan*/  lock; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
struct xmit_priv {TYPE_8__ pending_xmitbuf_queue; TYPE_7__ free_xmitbuf_queue; TYPE_6__ free_xmit_queue; TYPE_5__ bm_pending; TYPE_4__ vo_pending; TYPE_3__ vi_pending; TYPE_2__ bk_pending; TYPE_1__ be_pending; int /*<<< orphan*/  terminate_xmitthread_sema; int /*<<< orphan*/  xmit_sema; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtw_free_sema (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_spinlock_free (int /*<<< orphan*/ *) ; 

void  rtw_mfree_xmit_priv_lock (struct xmit_priv *pxmitpriv)
{
	_rtw_spinlock_free(&pxmitpriv->lock);
	_rtw_free_sema(&pxmitpriv->xmit_sema);
	_rtw_free_sema(&pxmitpriv->terminate_xmitthread_sema);

	_rtw_spinlock_free(&pxmitpriv->be_pending.lock);
	_rtw_spinlock_free(&pxmitpriv->bk_pending.lock);
	_rtw_spinlock_free(&pxmitpriv->vi_pending.lock);
	_rtw_spinlock_free(&pxmitpriv->vo_pending.lock);
	_rtw_spinlock_free(&pxmitpriv->bm_pending.lock);

	//_rtw_spinlock_free(&pxmitpriv->legacy_dz_queue.lock);
	//_rtw_spinlock_free(&pxmitpriv->apsd_queue.lock);

	_rtw_spinlock_free(&pxmitpriv->free_xmit_queue.lock);
	_rtw_spinlock_free(&pxmitpriv->free_xmitbuf_queue.lock);
	_rtw_spinlock_free(&pxmitpriv->pending_xmitbuf_queue.lock);
}