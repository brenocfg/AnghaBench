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
struct TYPE_4__ {int /*<<< orphan*/  h_proto; } ;
struct tx_packet_hdr {TYPE_2__ eth803_hdr; TYPE_2__ rfc1042_hdr; } ;
struct sk_buff {int len; scalar_t__ tail; struct rfc_1042_hdr* data; } ;
struct TYPE_3__ {int member_0; int member_1; int member_2; } ;
struct rfc_1042_hdr {int member_0; int member_1; int member_2; int member_4; int /*<<< orphan*/  snap_type; TYPE_1__ member_3; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ETH_ALEN ; 
 int LLC_SNAP_LEN ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct rfc_1042_hdr*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 struct tx_packet_hdr* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,struct rfc_1042_hdr*,int) ; 

__attribute__((used)) static int
mwifiex_11n_form_amsdu_pkt(struct sk_buff *skb_aggr,
			   struct sk_buff *skb_src, int *pad)

{
	int dt_offset;
	struct rfc_1042_hdr snap = {
		0xaa,		/* LLC DSAP */
		0xaa,		/* LLC SSAP */
		0x03,		/* LLC CTRL */
		{0x00, 0x00, 0x00},	/* SNAP OUI */
		0x0000		/* SNAP type */
			/*
			 * This field will be overwritten
			 * later with ethertype
			 */
	};
	struct tx_packet_hdr *tx_header;

	tx_header = skb_put(skb_aggr, sizeof(*tx_header));

	/* Copy DA and SA */
	dt_offset = 2 * ETH_ALEN;
	memcpy(&tx_header->eth803_hdr, skb_src->data, dt_offset);

	/* Copy SNAP header */
	snap.snap_type = ((struct ethhdr *)skb_src->data)->h_proto;

	dt_offset += sizeof(__be16);

	memcpy(&tx_header->rfc1042_hdr, &snap, sizeof(struct rfc_1042_hdr));

	skb_pull(skb_src, dt_offset);

	/* Update Length field */
	tx_header->eth803_hdr.h_proto = htons(skb_src->len + LLC_SNAP_LEN);

	/* Add payload */
	skb_put_data(skb_aggr, skb_src->data, skb_src->len);

	/* Add padding for new MSDU to start from 4 byte boundary */
	*pad = (4 - ((unsigned long)skb_aggr->tail & 0x3)) % 4;

	return skb_aggr->len + *pad;
}