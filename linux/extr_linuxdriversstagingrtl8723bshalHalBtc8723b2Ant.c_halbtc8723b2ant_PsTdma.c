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
struct TYPE_2__ {int bCurPsTdmaOn; int curPsTdma; int bPrePsTdmaOn; scalar_t__ prePsTdma; } ;
typedef  int /*<<< orphan*/  PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE_FW ; 
 int /*<<< orphan*/  ALGO_TRACE_FW_DETAIL ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SetFwPstdma (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 TYPE_1__* pCoexDm ; 

__attribute__((used)) static void halbtc8723b2ant_PsTdma(
	PBTC_COEXIST pBtCoexist, bool bForceExec, bool bTurnOn, u8 type
)
{
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW,
		(
			"[BTCoex], %s turn %s PS TDMA, type =%d\n",
			(bForceExec ? "force to" : ""),
			(bTurnOn ? "ON" : "OFF"),
			type
		)
	);
	pCoexDm->bCurPsTdmaOn = bTurnOn;
	pCoexDm->curPsTdma = type;

	if (!bForceExec) {
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_FW_DETAIL,
			(
				"[BTCoex], bPrePsTdmaOn = %d, bCurPsTdmaOn = %d!!\n",
				pCoexDm->bPrePsTdmaOn,
				pCoexDm->bCurPsTdmaOn
			)
		);
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_FW_DETAIL,
			(
				"[BTCoex], prePsTdma = %d, curPsTdma = %d!!\n",
				pCoexDm->prePsTdma, pCoexDm->curPsTdma
			)
		);

		if (
			(pCoexDm->bPrePsTdmaOn == pCoexDm->bCurPsTdmaOn) &&
			(pCoexDm->prePsTdma == pCoexDm->curPsTdma)
		)
			return;
	}

	if (bTurnOn) {
		switch (type) {
		case 1:
		default:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x1a, 0x1a, 0xe1, 0x90);
			break;
		case 2:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x12, 0x12, 0xe1, 0x90);
			break;
		case 3:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x1c, 0x3, 0xf1, 0x90);
			break;
		case 4:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x10, 0x03, 0xf1, 0x90);
			break;
		case 5:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x1a, 0x1a, 0x60, 0x90);
			break;
		case 6:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x12, 0x12, 0x60, 0x90);
			break;
		case 7:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x1c, 0x3, 0x70, 0x90);
			break;
		case 8:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xa3, 0x10, 0x3, 0x70, 0x90);
			break;
		case 9:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x1a, 0x1a, 0xe1, 0x90);
			break;
		case 10:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x12, 0x12, 0xe1, 0x90);
			break;
		case 11:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0xa, 0xa, 0xe1, 0x90);
			break;
		case 12:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x5, 0x5, 0xe1, 0x90);
			break;
		case 13:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x1a, 0x1a, 0x60, 0x90);
			break;
		case 14:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x12, 0x12, 0x60, 0x90);
			break;
		case 15:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0xa, 0xa, 0x60, 0x90);
			break;
		case 16:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x5, 0x5, 0x60, 0x90);
			break;
		case 17:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xa3, 0x2f, 0x2f, 0x60, 0x90);
			break;
		case 18:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x5, 0x5, 0xe1, 0x90);
			break;
		case 19:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x25, 0x25, 0xe1, 0x90);
			break;
		case 20:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x25, 0x25, 0x60, 0x90);
			break;
		case 21:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x15, 0x03, 0x70, 0x90);
			break;
		case 71:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x1a, 0x1a, 0xe1, 0x90);
			break;
		}
	} else {
		/*  disable PS tdma */
		switch (type) {
		case 0:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0x0, 0x0, 0x0, 0x40, 0x0);
			break;
		case 1:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0x0, 0x0, 0x0, 0x48, 0x0);
			break;
		default:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0x0, 0x0, 0x0, 0x40, 0x0);
			break;
		}
	}

	/*  update pre state */
	pCoexDm->bPrePsTdmaOn = pCoexDm->bCurPsTdmaOn;
	pCoexDm->prePsTdma = pCoexDm->curPsTdma;
}