#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tx_ts_record {int bAddBaReqInProgress; int bAddBaReqDelayed; int bUsingBa; int bDisable_AddBa; int /*<<< orphan*/  TxPendingBARecord; int /*<<< orphan*/  TxAdmittedBARecord; scalar_t__ TxCurSeq; int /*<<< orphan*/  TsCommonInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ResetBaEntry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetTsCommonInfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ResetTxTsEntry(struct tx_ts_record *pTS)
{
	ResetTsCommonInfo(&pTS->TsCommonInfo);
	pTS->TxCurSeq = 0;
	pTS->bAddBaReqInProgress = false;
	pTS->bAddBaReqDelayed = false;
	pTS->bUsingBa = false;
	pTS->bDisable_AddBa = false;
	ResetBaEntry(&pTS->TxAdmittedBARecord);
	ResetBaEntry(&pTS->TxPendingBARecord);
}