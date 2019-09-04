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
struct sta_info {int /*<<< orphan*/  sta_recvpriv; int /*<<< orphan*/  sta_xmitpriv; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_free_sta_recv_priv_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_free_sta_xmit_priv_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_spinlock_free (int /*<<< orphan*/ *) ; 

void rtw_mfree_stainfo(struct sta_info *psta)
{
_func_enter_;

	if(&psta->lock != NULL)
		 _rtw_spinlock_free(&psta->lock);

	_rtw_free_sta_xmit_priv_lock(&psta->sta_xmitpriv);
	_rtw_free_sta_recv_priv_lock(&psta->sta_recvpriv);
	
_func_exit_;	
}