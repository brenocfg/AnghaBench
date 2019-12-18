#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ipv6hdr {scalar_t__ hop_limit; scalar_t__* flow_lbl; scalar_t__ priority; } ;
typedef  struct ipv6hdr u8 ;
typedef  int u16 ;
struct TYPE_8__ {int flags; scalar_t__ mode; } ;
struct xfrm_state {TYPE_3__ props; struct ah_data* data; } ;
struct sk_buff {int network_header; scalar_t__ len; scalar_t__ data; int /*<<< orphan*/  ip_summed; } ;
struct scatterlist {int dummy; } ;
struct ip_auth_hdr {int nexthdr; struct ipv6hdr* auth_data; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;
struct ah_data {int icv_full_len; int icv_trunc_len; struct crypto_ahash* ahash; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_10__ {struct ipv6hdr* tmp; } ;
struct TYPE_6__ {int /*<<< orphan*/  hi; } ;
struct TYPE_7__ {TYPE_1__ input; } ;
struct TYPE_9__ {TYPE_2__ seq; } ;

/* Variables and functions */
 TYPE_5__* AH_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int EBADMSG ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int XFRM_ALIGN8 (int) ; 
 scalar_t__ XFRM_MODE_TUNNEL ; 
 int /*<<< orphan*/  XFRM_POLICY_IN ; 
 TYPE_4__* XFRM_SKB_CB (struct sk_buff*) ; 
 int XFRM_STATE_ESN ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  ah6_input_done ; 
 struct ipv6hdr* ah_alloc_tmp (struct crypto_ahash*,int,int) ; 
 struct scatterlist* ah_req_sg (struct crypto_ahash*,struct ahash_request*) ; 
 struct ipv6hdr* ah_tmp_auth (struct ipv6hdr*,int) ; 
 struct ipv6hdr* ah_tmp_icv (struct crypto_ahash*,int /*<<< orphan*/ *,int) ; 
 struct ahash_request* ah_tmp_req (struct crypto_ahash*,struct ipv6hdr*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,struct ipv6hdr*,scalar_t__) ; 
 int crypto_ahash_digest (struct ahash_request*) ; 
 scalar_t__ crypto_memneq (struct ipv6hdr*,struct ipv6hdr*,int) ; 
 int ipv6_authlen (struct ip_auth_hdr*) ; 
 scalar_t__ ipv6_clear_mutable_options (struct ipv6hdr*,int,int /*<<< orphan*/ ) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (struct ipv6hdr*) ; 
 int /*<<< orphan*/  memcpy (struct ipv6hdr*,struct ipv6hdr*,int) ; 
 int /*<<< orphan*/  memset (struct ipv6hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 int skb_cow_data (struct sk_buff*,int /*<<< orphan*/ ,struct sk_buff**) ; 
 struct ipv6hdr* skb_network_header (struct sk_buff*) ; 
 int skb_network_header_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int) ; 
 int skb_to_sgvec_nomark (struct sk_buff*,struct scatterlist*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ skb_unclone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ah6_input(struct xfrm_state *x, struct sk_buff *skb)
{
	/*
	 * Before process AH
	 * [IPv6][Ext1][Ext2][AH][Dest][Payload]
	 * |<-------------->| hdr_len
	 *
	 * To erase AH:
	 * Keeping copy of cleared headers. After AH processing,
	 * Moving the pointer of skb->network_header by using skb_pull as long
	 * as AH header length. Then copy back the copy as long as hdr_len
	 * If destination header following AH exists, copy it into after [Ext2].
	 *
	 * |<>|[IPv6][Ext1][Ext2][Dest][Payload]
	 * There is offset of AH before IPv6 header after the process.
	 */

	u8 *auth_data;
	u8 *icv;
	u8 *work_iph;
	struct sk_buff *trailer;
	struct crypto_ahash *ahash;
	struct ahash_request *req;
	struct scatterlist *sg;
	struct ip_auth_hdr *ah;
	struct ipv6hdr *ip6h;
	struct ah_data *ahp;
	u16 hdr_len;
	u16 ah_hlen;
	int nexthdr;
	int nfrags;
	int err = -ENOMEM;
	int seqhi_len = 0;
	__be32 *seqhi;
	int sglists = 0;
	struct scatterlist *seqhisg;

	if (!pskb_may_pull(skb, sizeof(struct ip_auth_hdr)))
		goto out;

	/* We are going to _remove_ AH header to keep sockets happy,
	 * so... Later this can change. */
	if (skb_unclone(skb, GFP_ATOMIC))
		goto out;

	skb->ip_summed = CHECKSUM_NONE;

	hdr_len = skb_network_header_len(skb);
	ah = (struct ip_auth_hdr *)skb->data;
	ahp = x->data;
	ahash = ahp->ahash;

	nexthdr = ah->nexthdr;
	ah_hlen = ipv6_authlen(ah);

	if (ah_hlen != XFRM_ALIGN8(sizeof(*ah) + ahp->icv_full_len) &&
	    ah_hlen != XFRM_ALIGN8(sizeof(*ah) + ahp->icv_trunc_len))
		goto out;

	if (!pskb_may_pull(skb, ah_hlen))
		goto out;

	err = skb_cow_data(skb, 0, &trailer);
	if (err < 0)
		goto out;
	nfrags = err;

	ah = (struct ip_auth_hdr *)skb->data;
	ip6h = ipv6_hdr(skb);

	skb_push(skb, hdr_len);

	if (x->props.flags & XFRM_STATE_ESN) {
		sglists = 1;
		seqhi_len = sizeof(*seqhi);
	}

	work_iph = ah_alloc_tmp(ahash, nfrags + sglists, hdr_len +
				ahp->icv_trunc_len + seqhi_len);
	if (!work_iph) {
		err = -ENOMEM;
		goto out;
	}

	auth_data = ah_tmp_auth((u8 *)work_iph, hdr_len);
	seqhi = (__be32 *)(auth_data + ahp->icv_trunc_len);
	icv = ah_tmp_icv(ahash, seqhi, seqhi_len);
	req = ah_tmp_req(ahash, icv);
	sg = ah_req_sg(ahash, req);
	seqhisg = sg + nfrags;

	memcpy(work_iph, ip6h, hdr_len);
	memcpy(auth_data, ah->auth_data, ahp->icv_trunc_len);
	memset(ah->auth_data, 0, ahp->icv_trunc_len);

	if (ipv6_clear_mutable_options(ip6h, hdr_len, XFRM_POLICY_IN))
		goto out_free;

	ip6h->priority    = 0;
	ip6h->flow_lbl[0] = 0;
	ip6h->flow_lbl[1] = 0;
	ip6h->flow_lbl[2] = 0;
	ip6h->hop_limit   = 0;

	sg_init_table(sg, nfrags + sglists);
	err = skb_to_sgvec_nomark(skb, sg, 0, skb->len);
	if (unlikely(err < 0))
		goto out_free;

	if (x->props.flags & XFRM_STATE_ESN) {
		/* Attach seqhi sg right after packet payload */
		*seqhi = XFRM_SKB_CB(skb)->seq.input.hi;
		sg_set_buf(seqhisg, seqhi, seqhi_len);
	}

	ahash_request_set_crypt(req, sg, icv, skb->len + seqhi_len);
	ahash_request_set_callback(req, 0, ah6_input_done, skb);

	AH_SKB_CB(skb)->tmp = work_iph;

	err = crypto_ahash_digest(req);
	if (err) {
		if (err == -EINPROGRESS)
			goto out;

		goto out_free;
	}

	err = crypto_memneq(icv, auth_data, ahp->icv_trunc_len) ? -EBADMSG : 0;
	if (err)
		goto out_free;

	skb->network_header += ah_hlen;
	memcpy(skb_network_header(skb), work_iph, hdr_len);
	__skb_pull(skb, ah_hlen + hdr_len);

	if (x->props.mode == XFRM_MODE_TUNNEL)
		skb_reset_transport_header(skb);
	else
		skb_set_transport_header(skb, -hdr_len);

	err = nexthdr;

out_free:
	kfree(work_iph);
out:
	return err;
}