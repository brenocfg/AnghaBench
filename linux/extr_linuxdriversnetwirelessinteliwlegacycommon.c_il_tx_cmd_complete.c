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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_8__ {int /*<<< orphan*/  write_ptr; int /*<<< orphan*/  read_ptr; } ;
struct il_tx_queue {int /*<<< orphan*/  time_stamp; struct il_cmd_meta* meta; struct il_device_cmd** cmd; TYPE_4__ q; } ;
struct TYPE_5__ {int sequence; } ;
struct il_rx_pkt {TYPE_1__ hdr; } ;
struct il_rx_buf {int /*<<< orphan*/ * page; } ;
struct il_priv {size_t cmd_queue; int /*<<< orphan*/  hcmd_lock; int /*<<< orphan*/  wait_command_queue; int /*<<< orphan*/  status; int /*<<< orphan*/  pci_dev; struct il_tx_queue* txq; } ;
struct TYPE_7__ {int /*<<< orphan*/  cmd; } ;
struct il_device_cmd {TYPE_3__ hdr; } ;
struct il_cmd_meta {int flags; int /*<<< orphan*/  (* callback ) (struct il_priv*,struct il_device_cmd*,struct il_rx_pkt*) ;TYPE_2__* source; } ;
struct TYPE_6__ {unsigned long reply_page; } ;

/* Variables and functions */
 int CMD_ASYNC ; 
 int CMD_WANT_SKB ; 
 int /*<<< orphan*/  D_INFO (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int SEQ_HUGE_FRAME ; 
 int SEQ_TO_IDX (int /*<<< orphan*/ ) ; 
 int SEQ_TO_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_HCMD_ACTIVE ; 
 scalar_t__ WARN (int,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct il_cmd_meta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct il_cmd_meta*,int /*<<< orphan*/ ) ; 
 int il_get_cmd_idx (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  il_get_cmd_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_hcmd_queue_reclaim (struct il_priv*,int,int,int) ; 
 int /*<<< orphan*/  il_print_hex_error (struct il_priv*,struct il_rx_pkt*,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  le16_to_cpu (int) ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct il_priv*,struct il_device_cmd*,struct il_rx_pkt*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void
il_tx_cmd_complete(struct il_priv *il, struct il_rx_buf *rxb)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	u16 sequence = le16_to_cpu(pkt->hdr.sequence);
	int txq_id = SEQ_TO_QUEUE(sequence);
	int idx = SEQ_TO_IDX(sequence);
	int cmd_idx;
	bool huge = !!(pkt->hdr.sequence & SEQ_HUGE_FRAME);
	struct il_device_cmd *cmd;
	struct il_cmd_meta *meta;
	struct il_tx_queue *txq = &il->txq[il->cmd_queue];
	unsigned long flags;

	/* If a Tx command is being handled and it isn't in the actual
	 * command queue then there a command routing bug has been introduced
	 * in the queue management code. */
	if (WARN
	    (txq_id != il->cmd_queue,
	     "wrong command queue %d (should be %d), sequence 0x%X readp=%d writep=%d\n",
	     txq_id, il->cmd_queue, sequence, il->txq[il->cmd_queue].q.read_ptr,
	     il->txq[il->cmd_queue].q.write_ptr)) {
		il_print_hex_error(il, pkt, 32);
		return;
	}

	cmd_idx = il_get_cmd_idx(&txq->q, idx, huge);
	cmd = txq->cmd[cmd_idx];
	meta = &txq->meta[cmd_idx];

	txq->time_stamp = jiffies;

	pci_unmap_single(il->pci_dev, dma_unmap_addr(meta, mapping),
			 dma_unmap_len(meta, len), PCI_DMA_BIDIRECTIONAL);

	/* Input error checking is done when commands are added to queue. */
	if (meta->flags & CMD_WANT_SKB) {
		meta->source->reply_page = (unsigned long)rxb_addr(rxb);
		rxb->page = NULL;
	} else if (meta->callback)
		meta->callback(il, cmd, pkt);

	spin_lock_irqsave(&il->hcmd_lock, flags);

	il_hcmd_queue_reclaim(il, txq_id, idx, cmd_idx);

	if (!(meta->flags & CMD_ASYNC)) {
		clear_bit(S_HCMD_ACTIVE, &il->status);
		D_INFO("Clearing HCMD_ACTIVE for command %s\n",
		       il_get_cmd_string(cmd->hdr.cmd));
		wake_up(&il->wait_command_queue);
	}

	/* Mark as unmapped */
	meta->flags = 0;

	spin_unlock_irqrestore(&il->hcmd_lock, flags);
}