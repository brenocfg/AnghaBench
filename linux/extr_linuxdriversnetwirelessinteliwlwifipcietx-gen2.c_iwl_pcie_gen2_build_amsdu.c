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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct iwl_trans {int dummy; } ;
struct iwl_tfh_tfd {int dummy; } ;
struct iwl_device_cmd {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int iwl_pcie_gen2_build_amsdu(struct iwl_trans *trans,
				     struct sk_buff *skb,
				     struct iwl_tfh_tfd *tfd, int start_len,
				     u8 hdr_len, struct iwl_device_cmd *dev_cmd)
{
#ifdef CONFIG_INET
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_tx_cmd *tx_cmd = (void *)dev_cmd->payload;
	struct ieee80211_hdr *hdr = (void *)skb->data;
	unsigned int snap_ip_tcp_hdrlen, ip_hdrlen, total_len, hdr_room;
	unsigned int mss = skb_shinfo(skb)->gso_size;
	u16 length, iv_len, amsdu_pad;
	u8 *start_hdr;
	struct iwl_tso_hdr_page *hdr_page;
	struct page **page_ptr;
	struct tso_t tso;

	/* if the packet is protected, then it must be CCMP or GCMP */
	iv_len = ieee80211_has_protected(hdr->frame_control) ?
		IEEE80211_CCMP_HDR_LEN : 0;

	trace_iwlwifi_dev_tx(trans->dev, skb, tfd, sizeof(*tfd),
			     &dev_cmd->hdr, start_len, 0);

	ip_hdrlen = skb_transport_header(skb) - skb_network_header(skb);
	snap_ip_tcp_hdrlen = 8 + ip_hdrlen + tcp_hdrlen(skb);
	total_len = skb->len - snap_ip_tcp_hdrlen - hdr_len - iv_len;
	amsdu_pad = 0;

	/* total amount of header we may need for this A-MSDU */
	hdr_room = DIV_ROUND_UP(total_len, mss) *
		(3 + snap_ip_tcp_hdrlen + sizeof(struct ethhdr)) + iv_len;

	/* Our device supports 9 segments at most, it will fit in 1 page */
	hdr_page = get_page_hdr(trans, hdr_room);
	if (!hdr_page)
		return -ENOMEM;

	get_page(hdr_page->page);
	start_hdr = hdr_page->pos;
	page_ptr = (void *)((u8 *)skb->cb + trans_pcie->page_offs);
	*page_ptr = hdr_page->page;
	memcpy(hdr_page->pos, skb->data + hdr_len, iv_len);
	hdr_page->pos += iv_len;

	/*
	 * Pull the ieee80211 header + IV to be able to use TSO core,
	 * we will restore it for the tx_status flow.
	 */
	skb_pull(skb, hdr_len + iv_len);

	/*
	 * Remove the length of all the headers that we don't actually
	 * have in the MPDU by themselves, but that we duplicate into
	 * all the different MSDUs inside the A-MSDU.
	 */
	le16_add_cpu(&tx_cmd->len, -snap_ip_tcp_hdrlen);

	tso_start(skb, &tso);

	while (total_len) {
		/* this is the data left for this subframe */
		unsigned int data_left = min_t(unsigned int, mss, total_len);
		struct sk_buff *csum_skb = NULL;
		unsigned int tb_len;
		dma_addr_t tb_phys;
		u8 *subf_hdrs_start = hdr_page->pos;

		total_len -= data_left;

		memset(hdr_page->pos, 0, amsdu_pad);
		hdr_page->pos += amsdu_pad;
		amsdu_pad = (4 - (sizeof(struct ethhdr) + snap_ip_tcp_hdrlen +
				  data_left)) & 0x3;
		ether_addr_copy(hdr_page->pos, ieee80211_get_DA(hdr));
		hdr_page->pos += ETH_ALEN;
		ether_addr_copy(hdr_page->pos, ieee80211_get_SA(hdr));
		hdr_page->pos += ETH_ALEN;

		length = snap_ip_tcp_hdrlen + data_left;
		*((__be16 *)hdr_page->pos) = cpu_to_be16(length);
		hdr_page->pos += sizeof(length);

		/*
		 * This will copy the SNAP as well which will be considered
		 * as MAC header.
		 */
		tso_build_hdr(skb, hdr_page->pos, &tso, data_left, !total_len);

		hdr_page->pos += snap_ip_tcp_hdrlen;

		tb_len = hdr_page->pos - start_hdr;
		tb_phys = dma_map_single(trans->dev, start_hdr,
					 tb_len, DMA_TO_DEVICE);
		if (unlikely(dma_mapping_error(trans->dev, tb_phys))) {
			dev_kfree_skb(csum_skb);
			goto out_err;
		}
		iwl_pcie_gen2_set_tb(trans, tfd, tb_phys, tb_len);
		trace_iwlwifi_dev_tx_tso_chunk(trans->dev, start_hdr, tb_len);
		/* add this subframe's headers' length to the tx_cmd */
		le16_add_cpu(&tx_cmd->len, hdr_page->pos - subf_hdrs_start);

		/* prepare the start_hdr for the next subframe */
		start_hdr = hdr_page->pos;

		/* put the payload */
		while (data_left) {
			tb_len = min_t(unsigned int, tso.size, data_left);
			tb_phys = dma_map_single(trans->dev, tso.data,
						 tb_len, DMA_TO_DEVICE);
			if (unlikely(dma_mapping_error(trans->dev, tb_phys))) {
				dev_kfree_skb(csum_skb);
				goto out_err;
			}
			iwl_pcie_gen2_set_tb(trans, tfd, tb_phys, tb_len);
			trace_iwlwifi_dev_tx_tso_chunk(trans->dev, tso.data,
						       tb_len);

			data_left -= tb_len;
			tso_build_data(skb, &tso, tb_len);
		}
	}

	/* re -add the WiFi header and IV */
	skb_push(skb, hdr_len + iv_len);

	return 0;

out_err:
#endif
	return -EINVAL;
}