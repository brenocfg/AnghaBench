#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int mpdu_density; int txop; int mcs; int stbc; int ba_size; int wcid; } ;
struct TYPE_5__ {TYPE_1__ ht; } ;
struct txentry_desc {int rate_mode; int key_idx; int length; TYPE_2__ u; int /*<<< orphan*/  flags; } ;
struct queue_entry {int entry_idx; TYPE_3__* queue; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {int qid; int winfo_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_TXD_ACK ; 
 int /*<<< orphan*/  ENTRY_TXD_ENCRYPT ; 
 int /*<<< orphan*/  ENTRY_TXD_GENERATE_SEQ ; 
 int /*<<< orphan*/  ENTRY_TXD_HT_AMPDU ; 
 int /*<<< orphan*/  ENTRY_TXD_HT_BW_40 ; 
 int /*<<< orphan*/  ENTRY_TXD_HT_MIMO_PS ; 
 int /*<<< orphan*/  ENTRY_TXD_HT_SHORT_GI ; 
 int /*<<< orphan*/  ENTRY_TXD_MORE_FRAG ; 
 int /*<<< orphan*/  ENTRY_TXD_REQ_TIMESTAMP ; 
 int /*<<< orphan*/  TXWI_W0_AMPDU ; 
 int /*<<< orphan*/  TXWI_W0_BW ; 
 int /*<<< orphan*/  TXWI_W0_CF_ACK ; 
 int /*<<< orphan*/  TXWI_W0_FRAG ; 
 int /*<<< orphan*/  TXWI_W0_MCS ; 
 int /*<<< orphan*/  TXWI_W0_MIMO_PS ; 
 int /*<<< orphan*/  TXWI_W0_MPDU_DENSITY ; 
 int /*<<< orphan*/  TXWI_W0_PHYMODE ; 
 int /*<<< orphan*/  TXWI_W0_SHORT_GI ; 
 int /*<<< orphan*/  TXWI_W0_STBC ; 
 int /*<<< orphan*/  TXWI_W0_TS ; 
 int /*<<< orphan*/  TXWI_W0_TX_OP ; 
 int /*<<< orphan*/  TXWI_W1_ACK ; 
 int /*<<< orphan*/  TXWI_W1_BW_WIN_SIZE ; 
 int /*<<< orphan*/  TXWI_W1_MPDU_TOTAL_BYTE_COUNT ; 
 int /*<<< orphan*/  TXWI_W1_NSEQ ; 
 int /*<<< orphan*/  TXWI_W1_PACKETID_ENTRY ; 
 int /*<<< orphan*/  TXWI_W1_PACKETID_QUEUE ; 
 int /*<<< orphan*/  TXWI_W1_WIRELESS_CLI_ID ; 
 int /*<<< orphan*/  _rt2x00_desc_write (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rt2800_drv_get_txwi (struct queue_entry*) ; 
 int /*<<< orphan*/  rt2x00_desc_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rt2x00_desc_write (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2800_write_tx_data(struct queue_entry *entry,
			  struct txentry_desc *txdesc)
{
	__le32 *txwi = rt2800_drv_get_txwi(entry);
	u32 word;
	int i;

	/*
	 * Initialize TX Info descriptor
	 */
	word = rt2x00_desc_read(txwi, 0);
	rt2x00_set_field32(&word, TXWI_W0_FRAG,
			   test_bit(ENTRY_TXD_MORE_FRAG, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W0_MIMO_PS,
			   test_bit(ENTRY_TXD_HT_MIMO_PS, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W0_CF_ACK, 0);
	rt2x00_set_field32(&word, TXWI_W0_TS,
			   test_bit(ENTRY_TXD_REQ_TIMESTAMP, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W0_AMPDU,
			   test_bit(ENTRY_TXD_HT_AMPDU, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W0_MPDU_DENSITY,
			   txdesc->u.ht.mpdu_density);
	rt2x00_set_field32(&word, TXWI_W0_TX_OP, txdesc->u.ht.txop);
	rt2x00_set_field32(&word, TXWI_W0_MCS, txdesc->u.ht.mcs);
	rt2x00_set_field32(&word, TXWI_W0_BW,
			   test_bit(ENTRY_TXD_HT_BW_40, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W0_SHORT_GI,
			   test_bit(ENTRY_TXD_HT_SHORT_GI, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W0_STBC, txdesc->u.ht.stbc);
	rt2x00_set_field32(&word, TXWI_W0_PHYMODE, txdesc->rate_mode);
	rt2x00_desc_write(txwi, 0, word);

	word = rt2x00_desc_read(txwi, 1);
	rt2x00_set_field32(&word, TXWI_W1_ACK,
			   test_bit(ENTRY_TXD_ACK, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W1_NSEQ,
			   test_bit(ENTRY_TXD_GENERATE_SEQ, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W1_BW_WIN_SIZE, txdesc->u.ht.ba_size);
	rt2x00_set_field32(&word, TXWI_W1_WIRELESS_CLI_ID,
			   test_bit(ENTRY_TXD_ENCRYPT, &txdesc->flags) ?
			   txdesc->key_idx : txdesc->u.ht.wcid);
	rt2x00_set_field32(&word, TXWI_W1_MPDU_TOTAL_BYTE_COUNT,
			   txdesc->length);
	rt2x00_set_field32(&word, TXWI_W1_PACKETID_QUEUE, entry->queue->qid);
	rt2x00_set_field32(&word, TXWI_W1_PACKETID_ENTRY, (entry->entry_idx % 3) + 1);
	rt2x00_desc_write(txwi, 1, word);

	/*
	 * Always write 0 to IV/EIV fields (word 2 and 3), hardware will insert
	 * the IV from the IVEIV register when TXD_W3_WIV is set to 0.
	 * When TXD_W3_WIV is set to 1 it will use the IV data
	 * from the descriptor. The TXWI_W1_WIRELESS_CLI_ID indicates which
	 * crypto entry in the registers should be used to encrypt the frame.
	 *
	 * Nulify all remaining words as well, we don't know how to program them.
	 */
	for (i = 2; i < entry->queue->winfo_size / sizeof(__le32); i++)
		_rt2x00_desc_write(txwi, i, 0);
}