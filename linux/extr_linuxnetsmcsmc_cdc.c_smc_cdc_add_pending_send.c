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
struct TYPE_2__ {int /*<<< orphan*/  prod; } ;
struct smc_connection {int /*<<< orphan*/  tx_cdc_seq; TYPE_1__ local_tx_ctrl; int /*<<< orphan*/  tx_curs_sent; } ;
struct smc_cdc_tx_pend {int /*<<< orphan*/  ctrl_seq; int /*<<< orphan*/  p_cursor; int /*<<< orphan*/  cursor; struct smc_connection* conn; } ;
struct smc_cdc_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON_MSG (int,char*) ; 
 int SMC_WR_BUF_SIZE ; 
 int SMC_WR_TX_PEND_PRIV_SIZE ; 
 int SMC_WR_TX_SIZE ; 

__attribute__((used)) static inline void smc_cdc_add_pending_send(struct smc_connection *conn,
					    struct smc_cdc_tx_pend *pend)
{
	BUILD_BUG_ON_MSG(
		sizeof(struct smc_cdc_msg) > SMC_WR_BUF_SIZE,
		"must increase SMC_WR_BUF_SIZE to at least sizeof(struct smc_cdc_msg)");
	BUILD_BUG_ON_MSG(
		sizeof(struct smc_cdc_msg) != SMC_WR_TX_SIZE,
		"must adapt SMC_WR_TX_SIZE to sizeof(struct smc_cdc_msg); if not all smc_wr upper layer protocols use the same message size any more, must start to set link->wr_tx_sges[i].length on each individual smc_wr_tx_send()");
	BUILD_BUG_ON_MSG(
		sizeof(struct smc_cdc_tx_pend) > SMC_WR_TX_PEND_PRIV_SIZE,
		"must increase SMC_WR_TX_PEND_PRIV_SIZE to at least sizeof(struct smc_cdc_tx_pend)");
	pend->conn = conn;
	pend->cursor = conn->tx_curs_sent;
	pend->p_cursor = conn->local_tx_ctrl.prod;
	pend->ctrl_seq = conn->tx_cdc_seq;
}