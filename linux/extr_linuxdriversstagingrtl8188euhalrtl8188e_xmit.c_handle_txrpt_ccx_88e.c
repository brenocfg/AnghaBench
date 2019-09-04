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
typedef  int /*<<< orphan*/  u8 ;
struct txrpt_ccx_88e {scalar_t__ pkt_ok; scalar_t__ int_ccx; } ;
struct adapter {int /*<<< orphan*/  xmitpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_SCTX_DONE_CCX_PKT_FAIL ; 
 int /*<<< orphan*/  RTW_SCTX_DONE_SUCCESS ; 
 int /*<<< orphan*/  rtw_ack_tx_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void handle_txrpt_ccx_88e(struct adapter *adapter, u8 *buf)
{
	struct txrpt_ccx_88e *txrpt_ccx = (struct txrpt_ccx_88e *)buf;

	if (txrpt_ccx->int_ccx) {
		if (txrpt_ccx->pkt_ok)
			rtw_ack_tx_done(&adapter->xmitpriv,
					RTW_SCTX_DONE_SUCCESS);
		else
			rtw_ack_tx_done(&adapter->xmitpriv,
					RTW_SCTX_DONE_CCX_PKT_FAIL);
	}
}