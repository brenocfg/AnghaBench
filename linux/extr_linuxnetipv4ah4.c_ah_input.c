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
struct iphdr {scalar_t__ check; scalar_t__ frag_off; scalar_t__ tos; scalar_t__ ttl; } ;
typedef  struct iphdr u8 ;
struct TYPE_8__ {int flags; scalar_t__ mode; } ;
struct xfrm_state {TYPE_3__ props; struct ah_data* data; } ;
struct sk_buff {int network_header; scalar_t__ len; scalar_t__ data; int /*<<< orphan*/  ip_summed; } ;
struct scatterlist {int dummy; } ;
struct ip_auth_hdr {int nexthdr; int hdrlen; struct iphdr* auth_data; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;
struct ah_data {int icv_full_len; int icv_trunc_len; struct crypto_ahash* ahash; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_10__ {struct iphdr* tmp; } ;
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
 int XFRM_ALIGN4 (int) ; 
 int XFRM_ALIGN8 (int) ; 
 scalar_t__ XFRM_MODE_TUNNEL ; 
 TYPE_4__* XFRM_SKB_CB (struct sk_buff*) ; 
 int XFRM_STATE_ALIGN4 ; 
 int XFRM_STATE_ESN ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 struct iphdr* ah_alloc_tmp (struct crypto_ahash*,int,int) ; 
 int /*<<< orphan*/  ah_input_done ; 
 struct scatterlist* ah_req_sg (struct crypto_ahash*,struct ahash_request*) ; 
 struct iphdr* ah_tmp_auth (int /*<<< orphan*/ *,int) ; 
 struct iphdr* ah_tmp_icv (struct crypto_ahash*,struct iphdr*,int) ; 
 struct ahash_request* ah_tmp_req (struct crypto_ahash*,struct iphdr*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,struct iphdr*,scalar_t__) ; 
 int crypto_ahash_digest (struct ahash_request*) ; 
 scalar_t__ crypto_memneq (struct iphdr*,struct iphdr*,int) ; 
 int ip_clear_mutable_options (struct iphdr*,int /*<<< orphan*/ *) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (struct iphdr*) ; 
 int /*<<< orphan*/  memcpy (struct iphdr*,struct iphdr*,int) ; 
 int /*<<< orphan*/  memset (struct iphdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 int skb_cow_data (struct sk_buff*,int /*<<< orphan*/ ,struct sk_buff**) ; 
 struct iphdr* skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int) ; 
 int skb_to_sgvec_nomark (struct sk_buff*,struct scatterlist*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ skb_unclone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ah_input(struct xfrm_state *x, struct sk_buff *skb)
{
	int ah_hlen;
	int ihl;
	int nexthdr;
	int nfrags;
	u8 *auth_data;
	u8 *icv;
	struct sk_buff *trailer;
	struct crypto_ahash *ahash;
	struct ahash_request *req;
	struct scatterlist *sg;
	struct iphdr *iph, *work_iph;
	struct ip_auth_hdr *ah;
	struct ah_data *ahp;
	int err = -ENOMEM;
	int seqhi_len = 0;
	__be32 *seqhi;
	int sglists = 0;
	struct scatterlist *seqhisg;

	if (!pskb_may_pull(skb, sizeof(*ah)))
		goto out;

	ah = (struct ip_auth_hdr *)skb->data;
	ahp = x->data;
	ahash = ahp->ahash;

	nexthdr = ah->nexthdr;
	ah_hlen = (ah->hdrlen + 2) << 2;

	if (x->props.flags & XFRM_STATE_ALIGN4) {
		if (ah_hlen != XFRM_ALIGN4(sizeof(*ah) + ahp->icv_full_len) &&
		    ah_hlen != XFRM_ALIGN4(sizeof(*ah) + ahp->icv_trunc_len))
			goto out;
	} else {
		if (ah_hlen != XFRM_ALIGN8(sizeof(*ah) + ahp->icv_full_len) &&
		    ah_hlen != XFRM_ALIGN8(sizeof(*ah) + ahp->icv_trunc_len))
			goto out;
	}

	if (!pskb_may_pull(skb, ah_hlen))
		goto out;

	/* We are going to _remove_ AH header to keep sockets happy,
	 * so... Later this can change. */
	if (skb_unclone(skb, GFP_ATOMIC))
		goto out;

	skb->ip_summed = CHECKSUM_NONE;


	if ((err = skb_cow_data(skb, 0, &trailer)) < 0)
		goto out;
	nfrags = err;

	ah = (struct ip_auth_hdr *)skb->data;
	iph = ip_hdr(skb);
	ihl = ip_hdrlen(skb);

	if (x->props.flags & XFRM_STATE_ESN) {
		sglists = 1;
		seqhi_len = sizeof(*seqhi);
	}

	work_iph = ah_alloc_tmp(ahash, nfrags + sglists, ihl +
				ahp->icv_trunc_len + seqhi_len);
	if (!work_iph) {
		err = -ENOMEM;
		goto out;
	}

	seqhi = (__be32 *)((char *)work_iph + ihl);
	auth_data = ah_tmp_auth(seqhi, seqhi_len);
	icv = ah_tmp_icv(ahash, auth_data, ahp->icv_trunc_len);
	req = ah_tmp_req(ahash, icv);
	sg = ah_req_sg(ahash, req);
	seqhisg = sg + nfrags;

	memcpy(work_iph, iph, ihl);
	memcpy(auth_data, ah->auth_data, ahp->icv_trunc_len);
	memset(ah->auth_data, 0, ahp->icv_trunc_len);

	iph->ttl = 0;
	iph->tos = 0;
	iph->frag_off = 0;
	iph->check = 0;
	if (ihl > sizeof(*iph)) {
		__be32 dummy;
		err = ip_clear_mutable_options(iph, &dummy);
		if (err)
			goto out_free;
	}

	skb_push(skb, ihl);

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
	ahash_request_set_callback(req, 0, ah_input_done, skb);

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
	memcpy(skb_network_header(skb), work_iph, ihl);
	__skb_pull(skb, ah_hlen + ihl);
	if (x->props.mode == XFRM_MODE_TUNNEL)
		skb_reset_transport_header(skb);
	else
		skb_set_transport_header(skb, -ihl);

	err = nexthdr;

out_free:
	kfree (work_iph);
out:
	return err;
}