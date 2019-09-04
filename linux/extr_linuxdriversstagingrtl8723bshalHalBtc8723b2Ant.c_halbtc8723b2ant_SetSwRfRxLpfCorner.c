#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int btRf0x1eBackup; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* fBtcSetRfReg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ;scalar_t__ bInitilized; } ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE_SW_EXEC ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BTC_RF_A ; 
 TYPE_4__* pCoexDm ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void halbtc8723b2ant_SetSwRfRxLpfCorner(
	PBTC_COEXIST pBtCoexist,
	bool bRxRfShrinkOn
)
{
	if (bRxRfShrinkOn) {
		/* Shrink RF Rx LPF corner */
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_SW_EXEC,
			("[BTCoex], Shrink RF Rx LPF corner!!\n")
		);
		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1e, 0xfffff, 0xffffc);
	} else {
		/* Resume RF Rx LPF corner */
		/*  After initialized, we can use pCoexDm->btRf0x1eBackup */
		if (pBtCoexist->bInitilized) {
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_SW_EXEC, ("[BTCoex], Resume RF Rx LPF corner!!\n"));
			pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1e, 0xfffff, pCoexDm->btRf0x1eBackup);
		}
	}
}