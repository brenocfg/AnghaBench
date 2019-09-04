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
typedef  int /*<<< orphan*/  u32 ;
struct rxdone_entry_desc {scalar_t__ cipher_status; int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  flags; } ;
struct queue_entry_priv_mmio {int /*<<< orphan*/ * desc; } ;
struct queue_entry {struct queue_entry_priv_mmio* priv_data; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  RXDONE_L2PAD ; 
 int /*<<< orphan*/  RXDONE_MY_BSS ; 
 int /*<<< orphan*/  RXD_W3_CIPHER_ERROR ; 
 int /*<<< orphan*/  RXD_W3_CRC_ERROR ; 
 int /*<<< orphan*/  RXD_W3_DECRYPTED ; 
 int /*<<< orphan*/  RXD_W3_L2PAD ; 
 int /*<<< orphan*/  RXD_W3_MY_BSS ; 
 scalar_t__ RX_CRYPTO_FAIL_MIC ; 
 scalar_t__ RX_CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  RX_FLAG_DECRYPTED ; 
 int /*<<< orphan*/  RX_FLAG_FAILED_FCS_CRC ; 
 int /*<<< orphan*/  RX_FLAG_IV_STRIPPED ; 
 int /*<<< orphan*/  RX_FLAG_MMIC_ERROR ; 
 int /*<<< orphan*/  RX_FLAG_MMIC_STRIPPED ; 
 int /*<<< orphan*/  rt2800_process_rxwi (struct queue_entry*,struct rxdone_entry_desc*) ; 
 int /*<<< orphan*/  rt2x00_desc_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rt2800mmio_fill_rxdone(struct queue_entry *entry,
			    struct rxdone_entry_desc *rxdesc)
{
	struct queue_entry_priv_mmio *entry_priv = entry->priv_data;
	__le32 *rxd = entry_priv->desc;
	u32 word;

	word = rt2x00_desc_read(rxd, 3);

	if (rt2x00_get_field32(word, RXD_W3_CRC_ERROR))
		rxdesc->flags |= RX_FLAG_FAILED_FCS_CRC;

	/*
	 * Unfortunately we don't know the cipher type used during
	 * decryption. This prevents us from correct providing
	 * correct statistics through debugfs.
	 */
	rxdesc->cipher_status = rt2x00_get_field32(word, RXD_W3_CIPHER_ERROR);

	if (rt2x00_get_field32(word, RXD_W3_DECRYPTED)) {
		/*
		 * Hardware has stripped IV/EIV data from 802.11 frame during
		 * decryption. Unfortunately the descriptor doesn't contain
		 * any fields with the EIV/IV data either, so they can't
		 * be restored by rt2x00lib.
		 */
		rxdesc->flags |= RX_FLAG_IV_STRIPPED;

		/*
		 * The hardware has already checked the Michael Mic and has
		 * stripped it from the frame. Signal this to mac80211.
		 */
		rxdesc->flags |= RX_FLAG_MMIC_STRIPPED;

		if (rxdesc->cipher_status == RX_CRYPTO_SUCCESS) {
			rxdesc->flags |= RX_FLAG_DECRYPTED;
		} else if (rxdesc->cipher_status == RX_CRYPTO_FAIL_MIC) {
			/*
			 * In order to check the Michael Mic, the packet must have
			 * been decrypted.  Mac80211 doesnt check the MMIC failure 
			 * flag to initiate MMIC countermeasures if the decoded flag
			 * has not been set.
			 */
			rxdesc->flags |= RX_FLAG_DECRYPTED;

			rxdesc->flags |= RX_FLAG_MMIC_ERROR;
		}
	}

	if (rt2x00_get_field32(word, RXD_W3_MY_BSS))
		rxdesc->dev_flags |= RXDONE_MY_BSS;

	if (rt2x00_get_field32(word, RXD_W3_L2PAD))
		rxdesc->dev_flags |= RXDONE_L2PAD;

	/*
	 * Process the RXWI structure that is at the start of the buffer.
	 */
	rt2800_process_rxwi(entry, rxdesc);
}