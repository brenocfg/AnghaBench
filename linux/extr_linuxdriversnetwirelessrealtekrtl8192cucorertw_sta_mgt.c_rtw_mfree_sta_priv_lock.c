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
struct sta_priv {TYPE_3__ sleep_q; TYPE_2__ wakeup_q; int /*<<< orphan*/  sta_hash_lock; TYPE_1__ free_sta_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtw_spinlock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_mfree_all_stainfo (struct sta_priv*) ; 

void rtw_mfree_sta_priv_lock(struct	sta_priv *pstapriv)
{
#ifdef CONFIG_AP_MODE
	struct wlan_acl_pool *pacl_list = &pstapriv->acl_list;
#endif

	 rtw_mfree_all_stainfo(pstapriv); //be done before free sta_hash_lock

	_rtw_spinlock_free(&pstapriv->free_sta_queue.lock);

	_rtw_spinlock_free(&pstapriv->sta_hash_lock);
	_rtw_spinlock_free(&pstapriv->wakeup_q.lock);
	_rtw_spinlock_free(&pstapriv->sleep_q.lock);

#ifdef CONFIG_AP_MODE
	_rtw_spinlock_free(&pstapriv->asoc_list_lock);
	_rtw_spinlock_free(&pstapriv->auth_list_lock);
	_rtw_spinlock_free(&pacl_list->acl_node_q.lock);
#endif

}