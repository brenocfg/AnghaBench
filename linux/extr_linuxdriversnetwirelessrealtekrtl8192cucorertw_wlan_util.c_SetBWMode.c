#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mlme_ext_priv {int dummy; } ;
struct TYPE_8__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_9__ {int /*<<< orphan*/  setbw_mutex; } ;
typedef  int /*<<< orphan*/  HT_CHANNEL_WIDTH ;

/* Variables and functions */
 int /*<<< orphan*/  _enter_critical_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* adapter_to_dvobj (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_hal_set_bwmode (TYPE_1__*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  rtw_set_oper_bw (TYPE_1__*,unsigned short) ; 
 int /*<<< orphan*/  rtw_set_oper_choffset (TYPE_1__*,unsigned char) ; 

void SetBWMode(_adapter *padapter, unsigned short bwmode, unsigned char channel_offset)
{
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

#ifdef CONFIG_DUALMAC_CONCURRENT
	//saved bw info
	rtw_set_oper_bw(padapter, bwmode);
	rtw_set_oper_choffset(padapter, channel_offset);
	dc_SetBWMode(padapter, bwmode, channel_offset);
#else //CONFIG_DUALMAC_CONCURRENT

	_enter_critical_mutex(&(adapter_to_dvobj(padapter)->setbw_mutex), NULL);

	//saved bw info
	rtw_set_oper_bw(padapter, bwmode);
	rtw_set_oper_choffset(padapter, channel_offset);

	rtw_hal_set_bwmode(padapter, (HT_CHANNEL_WIDTH)bwmode, channel_offset);

	_exit_critical_mutex(&(adapter_to_dvobj(padapter)->setbw_mutex), NULL);

#endif // CONFIG_DUALMAC_CONCURRENT
}