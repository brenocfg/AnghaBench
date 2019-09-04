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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct sta_recv_priv {TYPE_1__ defrag_q; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_spinlock_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void	_rtw_free_sta_recv_priv_lock(struct sta_recv_priv *psta_recvpriv)
{
_func_enter_;	

	_rtw_spinlock_free(&psta_recvpriv->lock);

	_rtw_spinlock_free(&(psta_recvpriv->defrag_q.lock));

_func_exit_;

}