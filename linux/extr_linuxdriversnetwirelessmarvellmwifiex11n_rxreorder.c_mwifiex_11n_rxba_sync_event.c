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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct mwifiex_rx_reorder_tbl {int dummy; } ;
struct mwifiex_private {int /*<<< orphan*/  adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
struct mwifiex_ie_types_rxba_sync {int* bitmap; int /*<<< orphan*/  mac; int /*<<< orphan*/  tid; int /*<<< orphan*/  bitmap_len; int /*<<< orphan*/  seq_num; TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EVT_D ; 
 int /*<<< orphan*/  INFO ; 
 int MAX_TID_VALUE ; 
 scalar_t__ TLV_TYPE_RXBA_SYNC ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct mwifiex_rx_reorder_tbl* mwifiex_11n_get_rx_reorder_tbl (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mwifiex_11n_rx_reorder_pkt (struct mwifiex_private*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mwifiex_dbg_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__*,scalar_t__) ; 

void mwifiex_11n_rxba_sync_event(struct mwifiex_private *priv,
				 u8 *event_buf, u16 len)
{
	struct mwifiex_ie_types_rxba_sync *tlv_rxba = (void *)event_buf;
	u16 tlv_type, tlv_len;
	struct mwifiex_rx_reorder_tbl *rx_reor_tbl_ptr;
	u8 i, j;
	u16 seq_num, tlv_seq_num, tlv_bitmap_len;
	int tlv_buf_left = len;
	int ret;
	u8 *tmp;

	mwifiex_dbg_dump(priv->adapter, EVT_D, "RXBA_SYNC event:",
			 event_buf, len);
	while (tlv_buf_left >= sizeof(*tlv_rxba)) {
		tlv_type = le16_to_cpu(tlv_rxba->header.type);
		tlv_len  = le16_to_cpu(tlv_rxba->header.len);
		if (tlv_type != TLV_TYPE_RXBA_SYNC) {
			mwifiex_dbg(priv->adapter, ERROR,
				    "Wrong TLV id=0x%x\n", tlv_type);
			return;
		}

		tlv_seq_num = le16_to_cpu(tlv_rxba->seq_num);
		tlv_bitmap_len = le16_to_cpu(tlv_rxba->bitmap_len);
		mwifiex_dbg(priv->adapter, INFO,
			    "%pM tid=%d seq_num=%d bitmap_len=%d\n",
			    tlv_rxba->mac, tlv_rxba->tid, tlv_seq_num,
			    tlv_bitmap_len);

		rx_reor_tbl_ptr =
			mwifiex_11n_get_rx_reorder_tbl(priv, tlv_rxba->tid,
						       tlv_rxba->mac);
		if (!rx_reor_tbl_ptr) {
			mwifiex_dbg(priv->adapter, ERROR,
				    "Can not find rx_reorder_tbl!");
			return;
		}

		for (i = 0; i < tlv_bitmap_len; i++) {
			for (j = 0 ; j < 8; j++) {
				if (tlv_rxba->bitmap[i] & (1 << j)) {
					seq_num = (MAX_TID_VALUE - 1) &
						(tlv_seq_num + i * 8 + j);

					mwifiex_dbg(priv->adapter, ERROR,
						    "drop packet,seq=%d\n",
						    seq_num);

					ret = mwifiex_11n_rx_reorder_pkt
					(priv, seq_num, tlv_rxba->tid,
					 tlv_rxba->mac, 0, NULL);

					if (ret)
						mwifiex_dbg(priv->adapter,
							    ERROR,
							    "Fail to drop packet");
				}
			}
		}

		tlv_buf_left -= (sizeof(*tlv_rxba) + tlv_len);
		tmp = (u8 *)tlv_rxba + tlv_len + sizeof(*tlv_rxba);
		tlv_rxba = (struct mwifiex_ie_types_rxba_sync *)tmp;
	}
}