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
struct TYPE_2__ {int max_txq_num; } ;
struct il_priv {int cmd_queue; TYPE_1__ hw_params; int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  il_cmd_queue_unmap (struct il_priv*) ; 
 int /*<<< orphan*/  il_tx_queue_unmap (struct il_priv*,int) ; 

__attribute__((used)) static void
il4965_txq_ctx_unmap(struct il_priv *il)
{
	int txq_id;

	if (!il->txq)
		return;

	/* Unmap DMA from host system and free skb's */
	for (txq_id = 0; txq_id < il->hw_params.max_txq_num; txq_id++)
		if (txq_id == il->cmd_queue)
			il_cmd_queue_unmap(il);
		else
			il_tx_queue_unmap(il, txq_id);
}