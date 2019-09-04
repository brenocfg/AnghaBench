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
typedef  int u32 ;
struct ath_hw {int dummy; } ;
struct ath_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx; } ;
struct ar5416_desc {int ds_ctl1; TYPE_1__ u; } ;

/* Variables and functions */
 struct ar5416_desc* AR5416DESC (struct ath_desc*) ; 
 int AR_BufLen ; 
 int AR_RxIntrReq ; 
 int ATH9K_RXDESC_INTREQ ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void ath9k_hw_setuprxdesc(struct ath_hw *ah, struct ath_desc *ds,
			  u32 size, u32 flags)
{
	struct ar5416_desc *ads = AR5416DESC(ds);

	ads->ds_ctl1 = size & AR_BufLen;
	if (flags & ATH9K_RXDESC_INTREQ)
		ads->ds_ctl1 |= AR_RxIntrReq;

	memset(&ads->u.rx, 0, sizeof(ads->u.rx));
}