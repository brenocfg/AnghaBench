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
struct ath10k_sdio_rx_data {int dummy; } ;
struct ath10k_htc_hdr {int /*<<< orphan*/  len; int /*<<< orphan*/  flags; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_HTC_FLAG_BUNDLE_MASK ; 
 int ENOMEM ; 
 size_t FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t HTC_HOST_MAX_MSG_PER_RX_BUNDLE ; 
 int ath10k_sdio_mbox_alloc_rx_pkt (struct ath10k_sdio_rx_data*,size_t,size_t,int,int) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_sdio_mbox_alloc_pkt_bundle(struct ath10k *ar,
					     struct ath10k_sdio_rx_data *rx_pkts,
					     struct ath10k_htc_hdr *htc_hdr,
					     size_t full_len, size_t act_len,
					     size_t *bndl_cnt)
{
	int ret, i;

	*bndl_cnt = FIELD_GET(ATH10K_HTC_FLAG_BUNDLE_MASK, htc_hdr->flags);

	if (*bndl_cnt > HTC_HOST_MAX_MSG_PER_RX_BUNDLE) {
		ath10k_warn(ar,
			    "HTC bundle length %u exceeds maximum %u\n",
			    le16_to_cpu(htc_hdr->len),
			    HTC_HOST_MAX_MSG_PER_RX_BUNDLE);
		return -ENOMEM;
	}

	/* Allocate bndl_cnt extra skb's for the bundle.
	 * The package containing the
	 * ATH10K_HTC_FLAG_BUNDLE_MASK flag is not included
	 * in bndl_cnt. The skb for that packet will be
	 * allocated separately.
	 */
	for (i = 0; i < *bndl_cnt; i++) {
		ret = ath10k_sdio_mbox_alloc_rx_pkt(&rx_pkts[i],
						    act_len,
						    full_len,
						    true,
						    false);
		if (ret)
			return ret;
	}

	return 0;
}