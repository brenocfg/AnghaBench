#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct rxdone_entry_desc {unsigned int size; int dev_flags; int flags; scalar_t__ rate_mode; int rate_idx; int flag; int /*<<< orphan*/  antenna; int /*<<< orphan*/  bw; int /*<<< orphan*/  encoding; int /*<<< orphan*/  enc_flags; int /*<<< orphan*/  rssi; int /*<<< orphan*/  signal; int /*<<< orphan*/  freq; int /*<<< orphan*/  band; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  mactime; } ;
struct TYPE_8__ {int /*<<< orphan*/  rx; } ;
struct TYPE_9__ {TYPE_2__ active; } ;
struct TYPE_10__ {TYPE_3__ ant; } ;
struct rt2x00_dev {TYPE_6__* ops; scalar_t__ flags; int /*<<< orphan*/  hw; TYPE_4__ link; int /*<<< orphan*/  curr_freq; int /*<<< orphan*/  curr_band; } ;
struct queue_entry {scalar_t__ flags; struct sk_buff* skb; TYPE_1__* queue; } ;
struct ieee80211_rx_status {unsigned int size; int dev_flags; int flags; scalar_t__ rate_mode; int rate_idx; int flag; int /*<<< orphan*/  antenna; int /*<<< orphan*/  bw; int /*<<< orphan*/  encoding; int /*<<< orphan*/  enc_flags; int /*<<< orphan*/  rssi; int /*<<< orphan*/  signal; int /*<<< orphan*/  freq; int /*<<< orphan*/  band; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  mactime; } ;
typedef  int /*<<< orphan*/  rxdesc ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_12__ {TYPE_5__* lib; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* clear_entry ) (struct queue_entry*) ;int /*<<< orphan*/  (* fill_rxdone ) (struct queue_entry*,struct rxdone_entry_desc*) ;} ;
struct TYPE_7__ {unsigned int data_size; struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  DEVICE_STATE_PRESENT ; 
 int /*<<< orphan*/  DUMP_FRAME_RXDONE ; 
 int /*<<< orphan*/  ENTRY_DATA_IO_FAILED ; 
 struct rxdone_entry_desc* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  Q_INDEX_DONE ; 
 scalar_t__ RATE_MODE_HT_GREENFIELD ; 
 scalar_t__ RATE_MODE_HT_MIX ; 
 int RXDONE_CRYPTO_IV ; 
 int RXDONE_L2PAD ; 
 int /*<<< orphan*/  RX_ENC_HT ; 
 int RX_FLAG_IV_STRIPPED ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 unsigned int ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_rx_ni (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct rxdone_entry_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rt2x00crypto_rx_insert_iv (struct sk_buff*,unsigned int,struct rxdone_entry_desc*) ; 
 int /*<<< orphan*/  rt2x00debug_dump_frame (struct rt2x00_dev*,int /*<<< orphan*/ ,struct queue_entry*) ; 
 int /*<<< orphan*/  rt2x00debug_update_crypto (struct rt2x00_dev*,struct rxdone_entry_desc*) ; 
 int /*<<< orphan*/  rt2x00lib_rxdone_check_ba (struct rt2x00_dev*,struct sk_buff*,struct rxdone_entry_desc*) ; 
 int /*<<< orphan*/  rt2x00lib_rxdone_check_ps (struct rt2x00_dev*,struct sk_buff*,struct rxdone_entry_desc*) ; 
 int rt2x00lib_rxdone_read_signal (struct rt2x00_dev*,struct rxdone_entry_desc*) ; 
 int /*<<< orphan*/  rt2x00link_update_stats (struct rt2x00_dev*,struct sk_buff*,struct rxdone_entry_desc*) ; 
 struct sk_buff* rt2x00queue_alloc_rxskb (struct queue_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00queue_index_inc (struct queue_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00queue_remove_l2pad (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  rt2x00queue_unmap_skb (struct queue_entry*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct queue_entry*,struct rxdone_entry_desc*) ; 
 int /*<<< orphan*/  stub2 (struct queue_entry*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 

void rt2x00lib_rxdone(struct queue_entry *entry, gfp_t gfp)
{
	struct rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	struct rxdone_entry_desc rxdesc;
	struct sk_buff *skb;
	struct ieee80211_rx_status *rx_status;
	unsigned int header_length;
	int rate_idx;

	if (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags) ||
	    !test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		goto submit_entry;

	if (test_bit(ENTRY_DATA_IO_FAILED, &entry->flags))
		goto submit_entry;

	/*
	 * Allocate a new sk_buffer. If no new buffer available, drop the
	 * received frame and reuse the existing buffer.
	 */
	skb = rt2x00queue_alloc_rxskb(entry, gfp);
	if (!skb)
		goto submit_entry;

	/*
	 * Unmap the skb.
	 */
	rt2x00queue_unmap_skb(entry);

	/*
	 * Extract the RXD details.
	 */
	memset(&rxdesc, 0, sizeof(rxdesc));
	rt2x00dev->ops->lib->fill_rxdone(entry, &rxdesc);

	/*
	 * Check for valid size in case we get corrupted descriptor from
	 * hardware.
	 */
	if (unlikely(rxdesc.size == 0 ||
		     rxdesc.size > entry->queue->data_size)) {
		rt2x00_err(rt2x00dev, "Wrong frame size %d max %d\n",
			   rxdesc.size, entry->queue->data_size);
		dev_kfree_skb(entry->skb);
		goto renew_skb;
	}

	/*
	 * The data behind the ieee80211 header must be
	 * aligned on a 4 byte boundary.
	 */
	header_length = ieee80211_get_hdrlen_from_skb(entry->skb);

	/*
	 * Hardware might have stripped the IV/EIV/ICV data,
	 * in that case it is possible that the data was
	 * provided separately (through hardware descriptor)
	 * in which case we should reinsert the data into the frame.
	 */
	if ((rxdesc.dev_flags & RXDONE_CRYPTO_IV) &&
	    (rxdesc.flags & RX_FLAG_IV_STRIPPED))
		rt2x00crypto_rx_insert_iv(entry->skb, header_length,
					  &rxdesc);
	else if (header_length &&
		 (rxdesc.size > header_length) &&
		 (rxdesc.dev_flags & RXDONE_L2PAD))
		rt2x00queue_remove_l2pad(entry->skb, header_length);

	/* Trim buffer to correct size */
	skb_trim(entry->skb, rxdesc.size);

	/*
	 * Translate the signal to the correct bitrate index.
	 */
	rate_idx = rt2x00lib_rxdone_read_signal(rt2x00dev, &rxdesc);
	if (rxdesc.rate_mode == RATE_MODE_HT_MIX ||
	    rxdesc.rate_mode == RATE_MODE_HT_GREENFIELD)
		rxdesc.encoding = RX_ENC_HT;

	/*
	 * Check if this is a beacon, and more frames have been
	 * buffered while we were in powersaving mode.
	 */
	rt2x00lib_rxdone_check_ps(rt2x00dev, entry->skb, &rxdesc);

	/*
	 * Check for incoming BlockAcks to match to the BlockAckReqs
	 * we've send out.
	 */
	rt2x00lib_rxdone_check_ba(rt2x00dev, entry->skb, &rxdesc);

	/*
	 * Update extra components
	 */
	rt2x00link_update_stats(rt2x00dev, entry->skb, &rxdesc);
	rt2x00debug_update_crypto(rt2x00dev, &rxdesc);
	rt2x00debug_dump_frame(rt2x00dev, DUMP_FRAME_RXDONE, entry);

	/*
	 * Initialize RX status information, and send frame
	 * to mac80211.
	 */
	rx_status = IEEE80211_SKB_RXCB(entry->skb);

	/* Ensure that all fields of rx_status are initialized
	 * properly. The skb->cb array was used for driver
	 * specific informations, so rx_status might contain
	 * garbage.
	 */
	memset(rx_status, 0, sizeof(*rx_status));

	rx_status->mactime = rxdesc.timestamp;
	rx_status->band = rt2x00dev->curr_band;
	rx_status->freq = rt2x00dev->curr_freq;
	rx_status->rate_idx = rate_idx;
	rx_status->signal = rxdesc.rssi;
	rx_status->flag = rxdesc.flags;
	rx_status->enc_flags = rxdesc.enc_flags;
	rx_status->encoding = rxdesc.encoding;
	rx_status->bw = rxdesc.bw;
	rx_status->antenna = rt2x00dev->link.ant.active.rx;

	ieee80211_rx_ni(rt2x00dev->hw, entry->skb);

renew_skb:
	/*
	 * Replace the skb with the freshly allocated one.
	 */
	entry->skb = skb;

submit_entry:
	entry->flags = 0;
	rt2x00queue_index_inc(entry, Q_INDEX_DONE);
	if (test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags) &&
	    test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt2x00dev->ops->lib->clear_entry(entry);
}