#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mlme_ext_priv {int dummy; } ;
struct TYPE_7__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_8__ {int /*<<< orphan*/  setch_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter_critical_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* adapter_to_dvobj (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_hal_set_chan (TYPE_1__*,unsigned char) ; 
 int /*<<< orphan*/  rtw_set_oper_ch (TYPE_1__*,unsigned char) ; 

void SelectChannel(_adapter *padapter, unsigned char channel)
{
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;	

#ifdef CONFIG_DUALMAC_CONCURRENT
	//saved channel info
	rtw_set_oper_ch(padapter, channel);
	dc_SelectChannel(padapter, channel);
#else //CONFIG_DUALMAC_CONCURRENT

	_enter_critical_mutex(&(adapter_to_dvobj(padapter)->setch_mutex), NULL);
	
	//saved channel info
	rtw_set_oper_ch(padapter, channel);

	rtw_hal_set_chan(padapter, channel);
	
	_exit_critical_mutex(&(adapter_to_dvobj(padapter)->setch_mutex), NULL);

#endif // CONFIG_DUALMAC_CONCURRENT
}