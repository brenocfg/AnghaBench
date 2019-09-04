#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct txentry_desc {int /*<<< orphan*/  flags; } ;
struct skb_frame_desc {int skb_dma; int /*<<< orphan*/  desc_len; int /*<<< orphan*/ * desc; } ;
struct queue_entry_priv_mmio {int /*<<< orphan*/ * desc; } ;
struct queue_entry {TYPE_2__* skb; TYPE_1__* queue; struct queue_entry_priv_mmio* priv_data; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {int len; } ;
struct TYPE_3__ {unsigned int winfo_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_TXD_BURST ; 
 int /*<<< orphan*/  ENTRY_TXD_ENCRYPT_IV ; 
 int /*<<< orphan*/  ENTRY_TXD_MORE_FRAG ; 
 int /*<<< orphan*/  TXD_DESC_SIZE ; 
 int /*<<< orphan*/  TXD_W0_SD_PTR0 ; 
 int /*<<< orphan*/  TXD_W1_BURST ; 
 int /*<<< orphan*/  TXD_W1_DMA_DONE ; 
 int /*<<< orphan*/  TXD_W1_LAST_SEC0 ; 
 int /*<<< orphan*/  TXD_W1_LAST_SEC1 ; 
 int /*<<< orphan*/  TXD_W1_SD_LEN0 ; 
 int /*<<< orphan*/  TXD_W1_SD_LEN1 ; 
 int /*<<< orphan*/  TXD_W2_SD_PTR1 ; 
 int /*<<< orphan*/  TXD_W3_QSEL ; 
 int /*<<< orphan*/  TXD_W3_WIV ; 
 struct skb_frame_desc* get_skb_frame_desc (TYPE_2__*) ; 
 int /*<<< orphan*/  rt2x00_desc_write (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (scalar_t__*,int /*<<< orphan*/ ,unsigned int const) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2800mmio_write_tx_desc(struct queue_entry *entry,
			      struct txentry_desc *txdesc)
{
	struct skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	struct queue_entry_priv_mmio *entry_priv = entry->priv_data;
	__le32 *txd = entry_priv->desc;
	u32 word;
	const unsigned int txwi_size = entry->queue->winfo_size;

	/*
	 * The buffers pointed by SD_PTR0/SD_LEN0 and SD_PTR1/SD_LEN1
	 * must contains a TXWI structure + 802.11 header + padding + 802.11
	 * data. We choose to have SD_PTR0/SD_LEN0 only contains TXWI and
	 * SD_PTR1/SD_LEN1 contains 802.11 header + padding + 802.11
	 * data. It means that LAST_SEC0 is always 0.
	 */

	/*
	 * Initialize TX descriptor
	 */
	word = 0;
	rt2x00_set_field32(&word, TXD_W0_SD_PTR0, skbdesc->skb_dma);
	rt2x00_desc_write(txd, 0, word);

	word = 0;
	rt2x00_set_field32(&word, TXD_W1_SD_LEN1, entry->skb->len);
	rt2x00_set_field32(&word, TXD_W1_LAST_SEC1,
			   !test_bit(ENTRY_TXD_MORE_FRAG, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W1_BURST,
			   test_bit(ENTRY_TXD_BURST, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W1_SD_LEN0, txwi_size);
	rt2x00_set_field32(&word, TXD_W1_LAST_SEC0, 0);
	rt2x00_set_field32(&word, TXD_W1_DMA_DONE, 0);
	rt2x00_desc_write(txd, 1, word);

	word = 0;
	rt2x00_set_field32(&word, TXD_W2_SD_PTR1,
			   skbdesc->skb_dma + txwi_size);
	rt2x00_desc_write(txd, 2, word);

	word = 0;
	rt2x00_set_field32(&word, TXD_W3_WIV,
			   !test_bit(ENTRY_TXD_ENCRYPT_IV, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W3_QSEL, 2);
	rt2x00_desc_write(txd, 3, word);

	/*
	 * Register descriptor details in skb frame descriptor.
	 */
	skbdesc->desc = txd;
	skbdesc->desc_len = TXD_DESC_SIZE;
}