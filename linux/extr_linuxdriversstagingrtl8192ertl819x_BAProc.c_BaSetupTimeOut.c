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
struct TYPE_3__ {int bValid; } ;
struct tx_ts_record {int bAddBaReqInProgress; int bAddBaReqDelayed; TYPE_1__ TxPendingBARecord; } ;
struct timer_list {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  Timer; } ;

/* Variables and functions */
 TYPE_2__ TxPendingBARecord ; 
 struct tx_ts_record* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct tx_ts_record* pTxTs ; 

void BaSetupTimeOut(struct timer_list *t)
{
	struct tx_ts_record *pTxTs = from_timer(pTxTs, t,
					      TxPendingBARecord.Timer);

	pTxTs->bAddBaReqInProgress = false;
	pTxTs->bAddBaReqDelayed = true;
	pTxTs->TxPendingBARecord.bValid = false;
}