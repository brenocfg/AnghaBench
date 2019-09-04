#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tx_servq {int dummy; } ;
struct TYPE_3__ {struct tx_servq be_q; struct tx_servq vo_q; struct tx_servq vi_q; struct tx_servq bk_q; } ;
struct sta_info {TYPE_1__ sta_xmitpriv; } ;
struct hw_xmit {int /*<<< orphan*/  accnt; } ;
struct __queue {int dummy; } ;
struct TYPE_4__ {struct __queue be_pending; struct __queue vo_pending; struct __queue vi_pending; struct __queue bk_pending; struct hw_xmit* hwxmits; } ;
struct _adapter {TYPE_2__ xmitpriv; } ;
typedef  int sint ;

/* Variables and functions */

__attribute__((used)) static inline struct tx_servq *get_sta_pending(struct _adapter *padapter,
					       struct  __queue **ppstapending,
					       struct sta_info *psta, sint up)
{

	struct tx_servq *ptxservq;
	struct hw_xmit *phwxmits =  padapter->xmitpriv.hwxmits;

	switch (up) {
	case 1:
	case 2:
		ptxservq = &(psta->sta_xmitpriv.bk_q);
		*ppstapending = &padapter->xmitpriv.bk_pending;
		(phwxmits + 3)->accnt++;
		break;
	case 4:
	case 5:
		ptxservq = &(psta->sta_xmitpriv.vi_q);
		*ppstapending = &padapter->xmitpriv.vi_pending;
		(phwxmits + 1)->accnt++;
		break;
	case 6:
	case 7:
		ptxservq = &(psta->sta_xmitpriv.vo_q);
		*ppstapending = &padapter->xmitpriv.vo_pending;
		(phwxmits + 0)->accnt++;
		break;
	case 0:
	case 3:
	default:
		ptxservq = &(psta->sta_xmitpriv.be_q);
		*ppstapending = &padapter->xmitpriv.be_pending;
		(phwxmits + 2)->accnt++;
		break;
	}
	return ptxservq;
}