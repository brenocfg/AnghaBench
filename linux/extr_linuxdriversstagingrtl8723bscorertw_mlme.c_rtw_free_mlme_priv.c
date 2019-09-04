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
struct mlme_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int /*<<< orphan*/  _rtw_free_mlme_priv (struct mlme_priv*) ; 

void rtw_free_mlme_priv(struct mlme_priv *pmlmepriv)
{
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("rtw_free_mlme_priv\n"));
	_rtw_free_mlme_priv(pmlmepriv);
}