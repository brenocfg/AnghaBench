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
struct sta_xmit_priv {int /*<<< orphan*/  apsd; int /*<<< orphan*/  legacy_dz; int /*<<< orphan*/  vo_q; int /*<<< orphan*/  vi_q; int /*<<< orphan*/  bk_q; int /*<<< orphan*/  be_q; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _init_txservq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_init_listhead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _rtw_spinlock_init (int /*<<< orphan*/ *) ; 

void	_rtw_init_sta_xmit_priv(struct sta_xmit_priv *psta_xmitpriv)
{	
	
_func_enter_;

	_rtw_memset((unsigned char *)psta_xmitpriv, 0, sizeof (struct sta_xmit_priv));

	_rtw_spinlock_init(&psta_xmitpriv->lock);
	
	//for(i = 0 ; i < MAX_NUMBLKS; i++)
	//	_init_txservq(&(psta_xmitpriv->blk_q[i]));

	_init_txservq(&psta_xmitpriv->be_q);
	_init_txservq(&psta_xmitpriv->bk_q);
	_init_txservq(&psta_xmitpriv->vi_q);
	_init_txservq(&psta_xmitpriv->vo_q);
	_rtw_init_listhead(&psta_xmitpriv->legacy_dz);
	_rtw_init_listhead(&psta_xmitpriv->apsd);
	
_func_exit_;	

}