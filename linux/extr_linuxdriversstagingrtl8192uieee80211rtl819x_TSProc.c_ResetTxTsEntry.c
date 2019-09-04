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
struct tx_ts_record {int add_ba_req_in_progress; int add_ba_req_delayed; int using_ba; int /*<<< orphan*/  tx_pending_ba_record; int /*<<< orphan*/  tx_admitted_ba_record; scalar_t__ tx_cur_seq; int /*<<< orphan*/  ts_common_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ResetBaEntry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetTsCommonInfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ResetTxTsEntry(struct tx_ts_record *pTS)
{
	ResetTsCommonInfo(&pTS->ts_common_info);
	pTS->tx_cur_seq = 0;
	pTS->add_ba_req_in_progress = false;
	pTS->add_ba_req_delayed = false;
	pTS->using_ba = false;
	ResetBaEntry(&pTS->tx_admitted_ba_record); //For BA Originator
	ResetBaEntry(&pTS->tx_pending_ba_record);
}