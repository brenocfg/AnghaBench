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
struct TYPE_2__ {int id; } ;
struct il_tx_queue {int sched_retry; TYPE_1__ q; } ;
struct il_priv {int /*<<< orphan*/  txq_ctx_active_msk; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*,char*,char*,int,int) ; 
 int /*<<< orphan*/  IL49_SCD_QUEUE_STATUS_BITS (int) ; 
 int IL49_SCD_QUEUE_STTS_REG_MSK ; 
 int IL49_SCD_QUEUE_STTS_REG_POS_ACTIVE ; 
 int IL49_SCD_QUEUE_STTS_REG_POS_SCD_ACK ; 
 int IL49_SCD_QUEUE_STTS_REG_POS_TXF ; 
 int IL49_SCD_QUEUE_STTS_REG_POS_WSL ; 
 int /*<<< orphan*/  il_wr_prph (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

void
il4965_tx_queue_set_status(struct il_priv *il, struct il_tx_queue *txq,
			   int tx_fifo_id, int scd_retry)
{
	int txq_id = txq->q.id;

	/* Find out whether to activate Tx queue */
	int active = test_bit(txq_id, &il->txq_ctx_active_msk) ? 1 : 0;

	/* Set up and activate */
	il_wr_prph(il, IL49_SCD_QUEUE_STATUS_BITS(txq_id),
		   (active << IL49_SCD_QUEUE_STTS_REG_POS_ACTIVE) |
		   (tx_fifo_id << IL49_SCD_QUEUE_STTS_REG_POS_TXF) |
		   (scd_retry << IL49_SCD_QUEUE_STTS_REG_POS_WSL) |
		   (scd_retry << IL49_SCD_QUEUE_STTS_REG_POS_SCD_ACK) |
		   IL49_SCD_QUEUE_STTS_REG_MSK);

	txq->sched_retry = scd_retry;

	D_INFO("%s %s Queue %d on AC %d\n", active ? "Activate" : "Deactivate",
	       scd_retry ? "BA" : "AC", txq_id, tx_fifo_id);
}