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
struct TYPE_2__ {int bCurLowPenaltyRa; int bPreLowPenaltyRa; } ;
typedef  int /*<<< orphan*/  PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE_SW ; 
 int /*<<< orphan*/  ALGO_TRACE_SW_DETAIL ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SetSwPenaltyTxRateAdaptive (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pCoexDm ; 

__attribute__((used)) static void halbtc8723b2ant_LowPenaltyRa(
	PBTC_COEXIST pBtCoexist, bool bForceExec, bool bLowPenaltyRa
)
{
	/* return; */
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW,
		(
			"[BTCoex], %s turn LowPenaltyRA = %s\n",
			(bForceExec ? "force to" : ""),
			(bLowPenaltyRa ? "ON" : "OFF")
		)
	);
	pCoexDm->bCurLowPenaltyRa = bLowPenaltyRa;

	if (!bForceExec) {
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_SW_DETAIL,
			(
				"[BTCoex], bPreLowPenaltyRa =%d, bCurLowPenaltyRa =%d\n",
				pCoexDm->bPreLowPenaltyRa,
				pCoexDm->bCurLowPenaltyRa
			)
		);

		if (pCoexDm->bPreLowPenaltyRa == pCoexDm->bCurLowPenaltyRa)
			return;
	}
	halbtc8723b2ant_SetSwPenaltyTxRateAdaptive(pBtCoexist, pCoexDm->bCurLowPenaltyRa);

	pCoexDm->bPreLowPenaltyRa = pCoexDm->bCurLowPenaltyRa;
}