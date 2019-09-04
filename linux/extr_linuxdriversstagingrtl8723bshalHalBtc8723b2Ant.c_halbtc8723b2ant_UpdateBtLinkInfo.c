#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int bBtLinkExist; int bPanExist; scalar_t__ bHidExist; scalar_t__ bA2dpExist; scalar_t__ bScoExist; } ;
struct TYPE_7__ {int bBtLinkExist; int bPanExist; int bScoOnly; int bA2dpOnly; int bPanOnly; int bHidOnly; scalar_t__ bHidExist; scalar_t__ bA2dpExist; scalar_t__ bScoExist; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;TYPE_2__ btLinkInfo; } ;
typedef  TYPE_1__* PBTC_COEXIST ;
typedef  TYPE_2__* PBTC_BT_LINK_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 TYPE_4__* pCoexSta ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8723b2ant_UpdateBtLinkInfo(PBTC_COEXIST pBtCoexist)
{
	PBTC_BT_LINK_INFO pBtLinkInfo = &pBtCoexist->btLinkInfo;
	bool bBtHsOn = false;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);

	pBtLinkInfo->bBtLinkExist = pCoexSta->bBtLinkExist;
	pBtLinkInfo->bScoExist = pCoexSta->bScoExist;
	pBtLinkInfo->bA2dpExist = pCoexSta->bA2dpExist;
	pBtLinkInfo->bPanExist = pCoexSta->bPanExist;
	pBtLinkInfo->bHidExist = pCoexSta->bHidExist;

	/*  work around for HS mode. */
	if (bBtHsOn) {
		pBtLinkInfo->bPanExist = true;
		pBtLinkInfo->bBtLinkExist = true;
	}

	/*  check if Sco only */
	if (
		pBtLinkInfo->bScoExist &&
		!pBtLinkInfo->bA2dpExist &&
		!pBtLinkInfo->bPanExist &&
		!pBtLinkInfo->bHidExist
	)
		pBtLinkInfo->bScoOnly = true;
	else
		pBtLinkInfo->bScoOnly = false;

	/*  check if A2dp only */
	if (
		!pBtLinkInfo->bScoExist &&
		pBtLinkInfo->bA2dpExist &&
		!pBtLinkInfo->bPanExist &&
		!pBtLinkInfo->bHidExist
	)
		pBtLinkInfo->bA2dpOnly = true;
	else
		pBtLinkInfo->bA2dpOnly = false;

	/*  check if Pan only */
	if (
		!pBtLinkInfo->bScoExist &&
		!pBtLinkInfo->bA2dpExist &&
		pBtLinkInfo->bPanExist &&
		!pBtLinkInfo->bHidExist
	)
		pBtLinkInfo->bPanOnly = true;
	else
		pBtLinkInfo->bPanOnly = false;

	/*  check if Hid only */
	if (
		!pBtLinkInfo->bScoExist &&
		!pBtLinkInfo->bA2dpExist &&
		!pBtLinkInfo->bPanExist &&
		pBtLinkInfo->bHidExist
	)
		pBtLinkInfo->bHidOnly = true;
	else
		pBtLinkInfo->bHidOnly = false;
}