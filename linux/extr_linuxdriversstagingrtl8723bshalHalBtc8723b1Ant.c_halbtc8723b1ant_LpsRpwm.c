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
typedef  void* u8 ;
struct TYPE_2__ {scalar_t__ curLps; scalar_t__ curRpwm; scalar_t__ preLps; scalar_t__ preRpwm; } ;
typedef  int /*<<< orphan*/  PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE_FW ; 
 int /*<<< orphan*/  ALGO_TRACE_FW_DETAIL ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_SetLpsRpwm (int /*<<< orphan*/ ,void*,void*) ; 
 TYPE_1__* pCoexDm ; 

__attribute__((used)) static void halbtc8723b1ant_LpsRpwm(
	PBTC_COEXIST pBtCoexist, bool bForceExec, u8 lpsVal, u8 rpwmVal
)
{
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW,
		(
			"[BTCoex], %s set lps/rpwm = 0x%x/0x%x\n",
			(bForceExec ? "force to" : ""),
			lpsVal,
			rpwmVal
		)
	);
	pCoexDm->curLps = lpsVal;
	pCoexDm->curRpwm = rpwmVal;

	if (!bForceExec) {
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_FW_DETAIL,
			(
				"[BTCoex], LPS-RxBeaconMode = 0x%x , LPS-RPWM = 0x%x!!\n",
				pCoexDm->curLps,
				pCoexDm->curRpwm
			)
		);

		if (
			(pCoexDm->preLps == pCoexDm->curLps) &&
			(pCoexDm->preRpwm == pCoexDm->curRpwm)
		) {
			BTC_PRINT(
				BTC_MSG_ALGORITHM,
				ALGO_TRACE_FW_DETAIL,
				(
					"[BTCoex], LPS-RPWM_Last = 0x%x , LPS-RPWM_Now = 0x%x!!\n",
					pCoexDm->preRpwm,
					pCoexDm->curRpwm
				)
			);

			return;
		}
	}
	halbtc8723b1ant_SetLpsRpwm(pBtCoexist, lpsVal, rpwmVal);

	pCoexDm->preLps = pCoexDm->curLps;
	pCoexDm->preRpwm = pCoexDm->curRpwm;
}