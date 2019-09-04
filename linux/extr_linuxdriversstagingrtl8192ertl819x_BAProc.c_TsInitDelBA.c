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
struct TYPE_2__ {scalar_t__ bValid; } ;
struct tx_ts_record {TYPE_1__ TxPendingBARecord; TYPE_1__ TxAdmittedBARecord; } ;
struct ts_common_info {int /*<<< orphan*/  Addr; } ;
struct rx_ts_record {TYPE_1__ RxAdmittedBARecord; } ;
struct rtllib_device {int dummy; } ;
typedef  enum tr_select { ____Placeholder_tr_select } tr_select ;

/* Variables and functions */
 int /*<<< orphan*/  DELBA_REASON_END_BA ; 
 int RX_DIR ; 
 scalar_t__ RxTsDeleteBA (struct rtllib_device*,struct rx_ts_record*) ; 
 int TX_DIR ; 
 scalar_t__ TxTsDeleteBA (struct rtllib_device*,struct tx_ts_record*) ; 
 int /*<<< orphan*/  rtllib_send_DELBA (struct rtllib_device*,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

void TsInitDelBA(struct rtllib_device *ieee,
		 struct ts_common_info *pTsCommonInfo,
		 enum tr_select TxRxSelect)
{
	if (TxRxSelect == TX_DIR) {
		struct tx_ts_record *pTxTs =
			 (struct tx_ts_record *)pTsCommonInfo;

		if (TxTsDeleteBA(ieee, pTxTs))
			rtllib_send_DELBA(ieee, pTsCommonInfo->Addr,
					  (pTxTs->TxAdmittedBARecord.bValid) ?
					 (&pTxTs->TxAdmittedBARecord) :
					(&pTxTs->TxPendingBARecord),
					 TxRxSelect, DELBA_REASON_END_BA);
	} else if (TxRxSelect == RX_DIR) {
		struct rx_ts_record *pRxTs =
				 (struct rx_ts_record *)pTsCommonInfo;
		if (RxTsDeleteBA(ieee, pRxTs))
			rtllib_send_DELBA(ieee, pTsCommonInfo->Addr,
					  &pRxTs->RxAdmittedBARecord,
					  TxRxSelect, DELBA_REASON_END_BA);
	}
}