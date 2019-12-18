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
struct iphdr {int ihl; int /*<<< orphan*/  daddr; scalar_t__ frag_off; scalar_t__ ttl; scalar_t__ tos; scalar_t__ check; int /*<<< orphan*/  tot_len; } ;
typedef  struct iphdr u8 ;
struct TYPE_8__ {int flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  spi; } ;
struct xfrm_state {TYPE_2__ props; TYPE_1__ id; struct ah_data* data; } ;
struct sk_buff {scalar_t__ len; } ;
struct scatterlist {int dummy; } ;
struct ip_auth_hdr {int hdrlen; struct iphdr* auth_data; void* seq_no; int /*<<< orphan*/  spi; scalar_t__ reserved; int /*<<< orphan*/  nexthdr; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;
struct ah_data {int icv_trunc_len; struct crypto_ahash* ahash; } ;
typedef  void* __be32 ;
struct TYPE_12__ {struct iphdr* tmp; } ;
struct TYPE_9__ {int /*<<< orphan*/  hi; int /*<<< orphan*/  low; } ;
struct TYPE_10__ {TYPE_3__ output; } ;
struct TYPE_11__ {TYPE_4__ seq; } ;

/* Variables and functions */
 TYPE_6__* AH_SKB_CB (struct sk_buff*) ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  IPPROTO_AH ; 
 int NET_XMIT_DROP ; 
 int XFRM_ALIGN4 (int) ; 
 int XFRM_ALIGN8 (int) ; 
 TYPE_5__* XFRM_SKB_CB (struct sk_buff*) ; 
 int XFRM_STATE_ALIGN4 ; 
 int XFRM_STATE_ESN ; 
 struct iphdr* ah_alloc_tmp (struct crypto_ahash*,int,int) ; 
 int /*<<< orphan*/  ah_output_done ; 
 struct scatterlist* ah_req_sg (struct crypto_ahash*,struct ahash_request*) ; 
 struct iphdr* ah_tmp_icv (struct crypto_ahash*,void**,int) ; 
 struct ahash_request* ah_tmp_req (struct crypto_ahash*,struct iphdr*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,struct iphdr*,scalar_t__) ; 
 int crypto_ahash_digest (struct ahash_request*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 struct ip_auth_hdr* ip_auth_hdr (struct sk_buff*) ; 
 int ip_clear_mutable_options (struct iphdr*,int /*<<< orphan*/ *) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (struct iphdr*) ; 
 int /*<<< orphan*/  memcpy (struct iphdr*,struct iphdr*,int) ; 
 int /*<<< orphan*/  memset (struct iphdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,void**,int) ; 
 int skb_cow_data (struct sk_buff*,int /*<<< orphan*/ ,struct sk_buff**) ; 
 int /*<<< orphan*/ * skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_to_sgvec_nomark (struct sk_buff*,struct scatterlist*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ah_output(struct xfrm_state *x, struct sk_buff *skb)
{
	int err;
	int nfrags;
	int ihl;
	u8 *icv;
	struct sk_buff *trailer;
	struct crypto_ahash *ahash;
	struct ahash_request *req;
	struct scatterlist *sg;
	struct iphdr *iph, *top_iph;
	struct ip_auth_hdr *ah;
	struct ah_data *ahp;
	int seqhi_len = 0;
	__be32 *seqhi;
	int sglists = 0;
	struct scatterlist *seqhisg;

	ahp = x->data;
	ahash = ahp->ahash;

	if ((err = skb_cow_data(skb, 0, &trailer)) < 0)
		goto out;
	nfrags = err;

	skb_push(skb, -skb_network_offset(skb));
	ah = ip_auth_hdr(skb);
	ihl = ip_hdrlen(skb);

	if (x->props.flags & XFRM_STATE_ESN) {
		sglists = 1;
		seqhi_len = sizeof(*seqhi);
	}
	err = -ENOMEM;
	iph = ah_alloc_tmp(ahash, nfrags + sglists, ihl + seqhi_len);
	if (!iph)
		goto out;
	seqhi = (__be32 *)((char *)iph + ihl);
	icv = ah_tmp_icv(ahash, seqhi, seqhi_len);
	req = ah_tmp_req(ahash, icv);
	sg = ah_req_sg(ahash, req);
	seqhisg = sg + nfrags;

	memset(ah->auth_data, 0, ahp->icv_trunc_len);

	top_iph = ip_hdr(skb);

	iph->tos = top_iph->tos;
	iph->ttl = top_iph->ttl;
	iph->frag_off = top_iph->frag_off;

	if (top_iph->ihl != 5) {
		iph->daddr = top_iph->daddr;
		memcpy(iph+1, top_iph+1, top_iph->ihl*4 - sizeof(struct iphdr));
		err = ip_clear_mutable_options(top_iph, &top_iph->daddr);
		if (err)
			goto out_free;
	}

	ah->nexthdr = *skb_mac_header(skb);
	*skb_mac_header(skb) = IPPROTO_AH;

	top_iph->tos = 0;
	top_iph->tot_len = htons(skb->len);
	top_iph->frag_off = 0;
	top_iph->ttl = 0;
	top_iph->check = 0;

	if (x->props.flags & XFRM_STATE_ALIGN4)
		ah->hdrlen  = (XFRM_ALIGN4(sizeof(*ah) + ahp->icv_trunc_len) >> 2) - 2;
	else
		ah->hdrlen  = (XFRM_ALIGN8(sizeof(*ah) + ahp->icv_trunc_len) >> 2) - 2;

	ah->reserved = 0;
	ah->spi = x->id.spi;
	ah->seq_no = htonl(XFRM_SKB_CB(skb)->seq.output.low);

	sg_init_table(sg, nfrags + sglists);
	err = skb_to_sgvec_nomark(skb, sg, 0, skb->len);
	if (unlikely(err < 0))
		goto out_free;

	if (x->props.flags & XFRM_STATE_ESN) {
		/* Attach seqhi sg right after packet payload */
		*seqhi = htonl(XFRM_SKB_CB(skb)->seq.output.hi);
		sg_set_buf(seqhisg, seqhi, seqhi_len);
	}
	ahash_request_set_crypt(req, sg, icv, skb->len + seqhi_len);
	ahash_request_set_callback(req, 0, ah_output_done, skb);

	AH_SKB_CB(skb)->tmp = iph;

	err = crypto_ahash_digest(req);
	if (err) {
		if (err == -EINPROGRESS)
			goto out;

		if (err == -ENOSPC)
			err = NET_XMIT_DROP;
		goto out_free;
	}

	memcpy(ah->auth_data, icv, ahp->icv_trunc_len);

	top_iph->tos = iph->tos;
	top_iph->ttl = iph->ttl;
	top_iph->frag_off = iph->frag_off;
	if (top_iph->ihl != 5) {
		top_iph->daddr = iph->daddr;
		memcpy(top_iph+1, iph+1, top_iph->ihl*4 - sizeof(struct iphdr));
	}

out_free:
	kfree(iph);
out:
	return err;
}