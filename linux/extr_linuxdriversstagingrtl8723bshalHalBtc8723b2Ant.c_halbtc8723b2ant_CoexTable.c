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
typedef  scalar_t__ u8 ;
typedef  void* u32 ;
struct TYPE_2__ {scalar_t__ curVal0x6c0; scalar_t__ curVal0x6c4; scalar_t__ curVal0x6c8; scalar_t__ curVal0x6cc; scalar_t__ preVal0x6c0; scalar_t__ preVal0x6c4; scalar_t__ preVal0x6c8; scalar_t__ preVal0x6cc; } ;
typedef  int /*<<< orphan*/  PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE_SW ; 
 int /*<<< orphan*/  ALGO_TRACE_SW_DETAIL ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SetCoexTable (int /*<<< orphan*/ ,void*,void*,void*,scalar_t__) ; 
 TYPE_1__* pCoexDm ; 

__attribute__((used)) static void halbtc8723b2ant_CoexTable(
	PBTC_COEXIST pBtCoexist,
	bool bForceExec,
	u32 val0x6c0,
	u32 val0x6c4,
	u32 val0x6c8,
	u8 val0x6cc
)
{
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW,
		(
			"[BTCoex], %s write Coex Table 0x6c0 = 0x%x, 0x6c4 = 0x%x, 0x6c8 = 0x%x, 0x6cc = 0x%x\n",
			(bForceExec ? "force to" : ""),
			val0x6c0,
			val0x6c4,
			val0x6c8,
			val0x6cc
		)
	);
	pCoexDm->curVal0x6c0 = val0x6c0;
	pCoexDm->curVal0x6c4 = val0x6c4;
	pCoexDm->curVal0x6c8 = val0x6c8;
	pCoexDm->curVal0x6cc = val0x6cc;

	if (!bForceExec) {
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_SW_DETAIL,
			(
				"[BTCoex], preVal0x6c0 = 0x%x, preVal0x6c4 = 0x%x, preVal0x6c8 = 0x%x, preVal0x6cc = 0x%x !!\n",
				pCoexDm->preVal0x6c0,
				pCoexDm->preVal0x6c4,
				pCoexDm->preVal0x6c8,
				pCoexDm->preVal0x6cc
			)
		);
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_SW_DETAIL,
			(
				"[BTCoex], curVal0x6c0 = 0x%x, curVal0x6c4 = 0x%x, curVal0x6c8 = 0x%x, curVal0x6cc = 0x%x !!\n",
				pCoexDm->curVal0x6c0,
				pCoexDm->curVal0x6c4,
				pCoexDm->curVal0x6c8,
				pCoexDm->curVal0x6cc
			)
		);

		if (
			(pCoexDm->preVal0x6c0 == pCoexDm->curVal0x6c0) &&
			(pCoexDm->preVal0x6c4 == pCoexDm->curVal0x6c4) &&
			(pCoexDm->preVal0x6c8 == pCoexDm->curVal0x6c8) &&
			(pCoexDm->preVal0x6cc == pCoexDm->curVal0x6cc)
		)
			return;
	}
	halbtc8723b2ant_SetCoexTable(pBtCoexist, val0x6c0, val0x6c4, val0x6c8, val0x6cc);

	pCoexDm->preVal0x6c0 = pCoexDm->curVal0x6c0;
	pCoexDm->preVal0x6c4 = pCoexDm->curVal0x6c4;
	pCoexDm->preVal0x6c8 = pCoexDm->curVal0x6c8;
	pCoexDm->preVal0x6cc = pCoexDm->curVal0x6cc;
}