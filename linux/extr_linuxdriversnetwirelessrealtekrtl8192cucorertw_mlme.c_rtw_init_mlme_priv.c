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
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int _rtw_init_mlme_priv (int /*<<< orphan*/ *) ; 

int	rtw_init_mlme_priv (_adapter *padapter)//(struct	mlme_priv *pmlmepriv)
{
	int	res;
_func_enter_;	
	res = _rtw_init_mlme_priv(padapter);// (pmlmepriv);
_func_exit_;	
	return res;
}