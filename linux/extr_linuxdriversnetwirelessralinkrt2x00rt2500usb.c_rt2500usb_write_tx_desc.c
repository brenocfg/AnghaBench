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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int ifs; int signal; int service; int length_low; int length_high; } ;
struct TYPE_7__ {TYPE_2__ plcp; } ;
struct txentry_desc {int retry_limit; scalar_t__ rate_mode; int length; int key_idx; int iv_offset; int /*<<< orphan*/  flags; TYPE_3__ u; int /*<<< orphan*/  cipher; } ;
struct skb_frame_desc {int /*<<< orphan*/  desc_len; int /*<<< orphan*/ * desc; int /*<<< orphan*/  flags; int /*<<< orphan*/ * iv; } ;
struct queue_entry {TYPE_1__* queue; TYPE_4__* skb; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_8__ {scalar_t__ data; } ;
struct TYPE_5__ {int aifs; int cw_min; int cw_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_TXD_ACK ; 
 int /*<<< orphan*/  ENTRY_TXD_ENCRYPT ; 
 int /*<<< orphan*/  ENTRY_TXD_FIRST_FRAGMENT ; 
 int /*<<< orphan*/  ENTRY_TXD_MORE_FRAG ; 
 int /*<<< orphan*/  ENTRY_TXD_REQ_TIMESTAMP ; 
 scalar_t__ RATE_MODE_OFDM ; 
 int /*<<< orphan*/  SKBDESC_DESC_IN_SKB ; 
 int /*<<< orphan*/  TXD_DESC_SIZE ; 
 int /*<<< orphan*/  TXD_W0_ACK ; 
 int /*<<< orphan*/  TXD_W0_CIPHER ; 
 int /*<<< orphan*/  TXD_W0_DATABYTE_COUNT ; 
 int /*<<< orphan*/  TXD_W0_IFS ; 
 int /*<<< orphan*/  TXD_W0_KEY_ID ; 
 int /*<<< orphan*/  TXD_W0_MORE_FRAG ; 
 int /*<<< orphan*/  TXD_W0_NEW_SEQ ; 
 int /*<<< orphan*/  TXD_W0_OFDM ; 
 int /*<<< orphan*/  TXD_W0_RETRY_LIMIT ; 
 int /*<<< orphan*/  TXD_W0_TIMESTAMP ; 
 int /*<<< orphan*/  TXD_W1_AIFS ; 
 int /*<<< orphan*/  TXD_W1_CWMAX ; 
 int /*<<< orphan*/  TXD_W1_CWMIN ; 
 int /*<<< orphan*/  TXD_W1_IV_OFFSET ; 
 int /*<<< orphan*/  TXD_W2_PLCP_LENGTH_HIGH ; 
 int /*<<< orphan*/  TXD_W2_PLCP_LENGTH_LOW ; 
 int /*<<< orphan*/  TXD_W2_PLCP_SERVICE ; 
 int /*<<< orphan*/  TXD_W2_PLCP_SIGNAL ; 
 int /*<<< orphan*/  _rt2x00_desc_write (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct skb_frame_desc* get_skb_frame_desc (TYPE_4__*) ; 
 int /*<<< orphan*/  rt2x00_desc_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rt2x00_desc_write (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2500usb_write_tx_desc(struct queue_entry *entry,
				    struct txentry_desc *txdesc)
{
	struct skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	__le32 *txd = (__le32 *) entry->skb->data;
	u32 word;

	/*
	 * Start writing the descriptor words.
	 */
	word = rt2x00_desc_read(txd, 0);
	rt2x00_set_field32(&word, TXD_W0_RETRY_LIMIT, txdesc->retry_limit);
	rt2x00_set_field32(&word, TXD_W0_MORE_FRAG,
			   test_bit(ENTRY_TXD_MORE_FRAG, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_ACK,
			   test_bit(ENTRY_TXD_ACK, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_TIMESTAMP,
			   test_bit(ENTRY_TXD_REQ_TIMESTAMP, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_OFDM,
			   (txdesc->rate_mode == RATE_MODE_OFDM));
	rt2x00_set_field32(&word, TXD_W0_NEW_SEQ,
			   test_bit(ENTRY_TXD_FIRST_FRAGMENT, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_IFS, txdesc->u.plcp.ifs);
	rt2x00_set_field32(&word, TXD_W0_DATABYTE_COUNT, txdesc->length);
	rt2x00_set_field32(&word, TXD_W0_CIPHER, !!txdesc->cipher);
	rt2x00_set_field32(&word, TXD_W0_KEY_ID, txdesc->key_idx);
	rt2x00_desc_write(txd, 0, word);

	word = rt2x00_desc_read(txd, 1);
	rt2x00_set_field32(&word, TXD_W1_IV_OFFSET, txdesc->iv_offset);
	rt2x00_set_field32(&word, TXD_W1_AIFS, entry->queue->aifs);
	rt2x00_set_field32(&word, TXD_W1_CWMIN, entry->queue->cw_min);
	rt2x00_set_field32(&word, TXD_W1_CWMAX, entry->queue->cw_max);
	rt2x00_desc_write(txd, 1, word);

	word = rt2x00_desc_read(txd, 2);
	rt2x00_set_field32(&word, TXD_W2_PLCP_SIGNAL, txdesc->u.plcp.signal);
	rt2x00_set_field32(&word, TXD_W2_PLCP_SERVICE, txdesc->u.plcp.service);
	rt2x00_set_field32(&word, TXD_W2_PLCP_LENGTH_LOW,
			   txdesc->u.plcp.length_low);
	rt2x00_set_field32(&word, TXD_W2_PLCP_LENGTH_HIGH,
			   txdesc->u.plcp.length_high);
	rt2x00_desc_write(txd, 2, word);

	if (test_bit(ENTRY_TXD_ENCRYPT, &txdesc->flags)) {
		_rt2x00_desc_write(txd, 3, skbdesc->iv[0]);
		_rt2x00_desc_write(txd, 4, skbdesc->iv[1]);
	}

	/*
	 * Register descriptor details in skb frame descriptor.
	 */
	skbdesc->flags |= SKBDESC_DESC_IN_SKB;
	skbdesc->desc = txd;
	skbdesc->desc_len = TXD_DESC_SIZE;
}