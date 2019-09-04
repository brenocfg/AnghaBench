#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {scalar_t__ bA2dpExist; scalar_t__ bPanExist; scalar_t__ bHidExist; scalar_t__ bScoExist; int /*<<< orphan*/  bBtLinkExist; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;TYPE_2__ btLinkInfo; } ;
typedef  TYPE_1__* PBTC_COEXIST ;
typedef  TYPE_2__* PBTC_BT_LINK_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE ; 
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int BT_8723B_2ANT_COEX_ALGO_A2DP ; 
 int BT_8723B_2ANT_COEX_ALGO_A2DP_PANHS ; 
 int BT_8723B_2ANT_COEX_ALGO_HID ; 
 int BT_8723B_2ANT_COEX_ALGO_HID_A2DP ; 
 int BT_8723B_2ANT_COEX_ALGO_HID_A2DP_PANEDR ; 
 int BT_8723B_2ANT_COEX_ALGO_PANEDR ; 
 int BT_8723B_2ANT_COEX_ALGO_PANEDR_A2DP ; 
 int BT_8723B_2ANT_COEX_ALGO_PANEDR_HID ; 
 int BT_8723B_2ANT_COEX_ALGO_PANHS ; 
 int BT_8723B_2ANT_COEX_ALGO_SCO ; 
 int BT_8723B_2ANT_COEX_ALGO_UNDEFINED ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u8 halbtc8723b2ant_ActionAlgorithm(PBTC_COEXIST pBtCoexist)
{
	PBTC_BT_LINK_INFO pBtLinkInfo = &pBtCoexist->btLinkInfo;
	bool bBtHsOn = false;
	u8 algorithm = BT_8723B_2ANT_COEX_ALGO_UNDEFINED;
	u8 numOfDiffProfile = 0;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);

	if (!pBtLinkInfo->bBtLinkExist) {
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], No BT link exists!!!\n"));
		return algorithm;
	}

	if (pBtLinkInfo->bScoExist)
		numOfDiffProfile++;

	if (pBtLinkInfo->bHidExist)
		numOfDiffProfile++;

	if (pBtLinkInfo->bPanExist)
		numOfDiffProfile++;

	if (pBtLinkInfo->bA2dpExist)
		numOfDiffProfile++;

	if (numOfDiffProfile == 1) {
		if (pBtLinkInfo->bScoExist) {
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO only\n"));
			algorithm = BT_8723B_2ANT_COEX_ALGO_SCO;
		} else {
			if (pBtLinkInfo->bHidExist) {
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], HID only\n"));
				algorithm = BT_8723B_2ANT_COEX_ALGO_HID;
			} else if (pBtLinkInfo->bA2dpExist) {
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], A2DP only\n"));
				algorithm = BT_8723B_2ANT_COEX_ALGO_A2DP;
			} else if (pBtLinkInfo->bPanExist) {
				if (bBtHsOn) {
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], PAN(HS) only\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANHS;
				} else {
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], PAN(EDR) only\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR;
				}
			}
		}
	} else if (numOfDiffProfile == 2) {
		if (pBtLinkInfo->bScoExist) {
			if (pBtLinkInfo->bHidExist) {
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO + HID\n"));
				algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
			} else if (pBtLinkInfo->bA2dpExist) {
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO + A2DP ==> SCO\n"));
				algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
			} else if (pBtLinkInfo->bPanExist) {
				if (bBtHsOn) {
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO + PAN(HS)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_SCO;
				} else {
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO + PAN(EDR)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				}
			}
		} else {
			if (
				pBtLinkInfo->bHidExist &&
				pBtLinkInfo->bA2dpExist
			) {
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], HID + A2DP\n"));
				algorithm = BT_8723B_2ANT_COEX_ALGO_HID_A2DP;
			} else if (
				pBtLinkInfo->bHidExist &&
				pBtLinkInfo->bPanExist
			) {
				if (bBtHsOn) {
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], HID + PAN(HS)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_HID;
				} else {
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], HID + PAN(EDR)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				}
			} else if (
				pBtLinkInfo->bPanExist &&
				pBtLinkInfo->bA2dpExist
			) {
				if (bBtHsOn) {
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], A2DP + PAN(HS)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_A2DP_PANHS;
				} else {
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], A2DP + PAN(EDR)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_A2DP;
				}
			}
		}
	} else if (numOfDiffProfile == 3) {
		if (pBtLinkInfo->bScoExist) {
			if (
				pBtLinkInfo->bHidExist &&
				pBtLinkInfo->bA2dpExist
			) {
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_TRACE,
					("[BTCoex], SCO + HID + A2DP ==> HID\n")
				);
				algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
			} else if (
				pBtLinkInfo->bHidExist &&
				pBtLinkInfo->bPanExist
			) {
				if (bBtHsOn) {
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], SCO + HID + PAN(HS)\n")
					);
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				} else {
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], SCO + HID + PAN(EDR)\n")
					);
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				}
			} else if (
				pBtLinkInfo->bPanExist &&
				pBtLinkInfo->bA2dpExist
			) {
				if (bBtHsOn) {
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO + A2DP + PAN(HS)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				} else {
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO + A2DP + PAN(EDR) ==> HID\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				}
			}
		} else {
			if (
				pBtLinkInfo->bHidExist &&
				pBtLinkInfo->bPanExist &&
				pBtLinkInfo->bA2dpExist
			) {
				if (bBtHsOn) {
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], HID + A2DP + PAN(HS)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_HID_A2DP;
				} else {
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], HID + A2DP + PAN(EDR)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_HID_A2DP_PANEDR;
				}
			}
		}
	} else if (numOfDiffProfile >= 3) {
		if (pBtLinkInfo->bScoExist) {
			if (
				pBtLinkInfo->bHidExist &&
				pBtLinkInfo->bPanExist &&
				pBtLinkInfo->bA2dpExist
			) {
				if (bBtHsOn) {
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Error!!! SCO + HID + A2DP + PAN(HS)\n"));

				} else {
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO + HID + A2DP + PAN(EDR) ==>PAN(EDR)+HID\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				}
			}
		}
	}

	return algorithm;
}