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
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {TYPE_1__ sta_pending; } ;
struct TYPE_15__ {int /*<<< orphan*/  lock; } ;
struct TYPE_16__ {TYPE_7__ sta_pending; } ;
struct TYPE_13__ {int /*<<< orphan*/  lock; } ;
struct TYPE_14__ {TYPE_5__ sta_pending; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; } ;
struct TYPE_12__ {TYPE_3__ sta_pending; } ;
struct sta_xmit_priv {TYPE_2__ vo_q; TYPE_8__ vi_q; TYPE_6__ bk_q; TYPE_4__ be_q; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_spinlock_free (int /*<<< orphan*/ *) ; 

void	_rtw_free_sta_xmit_priv_lock(struct sta_xmit_priv *psta_xmitpriv)
{
_func_enter_;

	_rtw_spinlock_free(&psta_xmitpriv->lock);

	_rtw_spinlock_free(&(psta_xmitpriv->be_q.sta_pending.lock));
	_rtw_spinlock_free(&(psta_xmitpriv->bk_q.sta_pending.lock));
	_rtw_spinlock_free(&(psta_xmitpriv->vi_q.sta_pending.lock));
	_rtw_spinlock_free(&(psta_xmitpriv->vo_q.sta_pending.lock));
_func_exit_;	
}