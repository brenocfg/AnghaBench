#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* pTW_IDENTITY ;
struct TYPE_8__ {scalar_t__ Id; } ;
struct TYPE_10__ {scalar_t__ (* dsEntry ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct TYPE_10__* next; TYPE_1__ identity; } ;
typedef  TYPE_3__ activeDS ;
struct TYPE_9__ {scalar_t__ Id; } ;
typedef  scalar_t__ TW_UINT16 ;
typedef  int /*<<< orphan*/  TW_MEMREF ;

/* Variables and functions */
 int /*<<< orphan*/  DAT_IDENTITY ; 
 int /*<<< orphan*/  DG_CONTROL ; 
 int /*<<< orphan*/  DSM_twCC ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  MSG_CLOSEDS ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TWCC_NODS ; 
 int /*<<< orphan*/  TWCC_SEQERROR ; 
 int /*<<< orphan*/  TWCC_SUCCESS ; 
 scalar_t__ TWRC_FAILURE ; 
 scalar_t__ TWRC_SUCCESS ; 
 TYPE_3__* activeSources ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

TW_UINT16 TWAIN_CloseDS (pTW_IDENTITY pOrigin, TW_MEMREF pData)
{
	TW_UINT16 twRC = TWRC_SUCCESS;
	pTW_IDENTITY pIdentity = (pTW_IDENTITY) pData;
	activeDS *currentDS = NULL, *prevDS = NULL;

	TRACE ("DG_CONTROL/DAT_IDENTITY/MSG_CLOSEDS\n");

	for (currentDS = activeSources; currentDS; currentDS = currentDS->next) {
		if (currentDS->identity.Id == pIdentity->Id)
			break;
		prevDS = currentDS;
	}
	if (!currentDS) {
		DSM_twCC = TWCC_NODS;
		return TWRC_FAILURE;
	}
	twRC = currentDS->dsEntry (pOrigin, DG_CONTROL, DAT_IDENTITY, MSG_CLOSEDS, pData);
	/* This causes crashes due to still open Windows, so leave out for now.
	 * FreeLibrary (currentDS->hmod);
	 */
	if (prevDS)
		prevDS->next = currentDS->next;
	else
		activeSources = currentDS->next;
	HeapFree (GetProcessHeap(), 0, currentDS);
	if (twRC == TWRC_SUCCESS)
		DSM_twCC = TWCC_SUCCESS;
	else /* FIXME: unclear how to get TWCC */
		DSM_twCC = TWCC_SEQERROR;
	return twRC;
}