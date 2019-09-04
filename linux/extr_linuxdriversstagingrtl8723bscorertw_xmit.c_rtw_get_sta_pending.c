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
typedef  int u8 ;
struct tx_servq {int dummy; } ;
struct TYPE_2__ {struct tx_servq be_q; struct tx_servq vo_q; struct tx_servq vi_q; struct tx_servq bk_q; } ;
struct sta_info {TYPE_1__ sta_xmitpriv; } ;
struct adapter {int dummy; } ;
typedef  int sint ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_xmit_c_ ; 

struct tx_servq *rtw_get_sta_pending(struct adapter *padapter, struct sta_info *psta, sint up, u8 *ac)
{
	struct tx_servq *ptxservq = NULL;

	switch (up) {
	case 1:
	case 2:
		ptxservq = &(psta->sta_xmitpriv.bk_q);
		*(ac) = 3;
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_, ("rtw_get_sta_pending : BK\n"));
		break;

	case 4:
	case 5:
		ptxservq = &(psta->sta_xmitpriv.vi_q);
		*(ac) = 1;
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_, ("rtw_get_sta_pending : VI\n"));
		break;

	case 6:
	case 7:
		ptxservq = &(psta->sta_xmitpriv.vo_q);
		*(ac) = 0;
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_, ("rtw_get_sta_pending : VO\n"));
		break;

	case 0:
	case 3:
	default:
		ptxservq = &(psta->sta_xmitpriv.be_q);
		*(ac) = 2;
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_, ("rtw_get_sta_pending : BE\n"));
	break;

	}

	return ptxservq;
}