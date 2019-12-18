#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int flags; } ;
struct xfrm_state {TYPE_1__ props; struct crypto_aead* data; } ;
struct sk_buff {int len; int /*<<< orphan*/  ip_summed; } ;
struct scatterlist {int dummy; } ;
struct ip_esp_hdr {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {void* tmp; } ;
struct TYPE_5__ {int nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 TYPE_3__* ESP_SKB_CB (struct sk_buff*) ; 
 int XFRM_STATE_ESN ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,struct scatterlist*,struct scatterlist*,int,int /*<<< orphan*/ *) ; 
 int crypto_aead_decrypt (struct aead_request*) ; 
 int crypto_aead_ivsize (struct crypto_aead*) ; 
 int esp6_input_done2 (struct sk_buff*,int) ; 
 void* esp_alloc_tmp (struct crypto_aead*,int,int) ; 
 int /*<<< orphan*/  esp_input_done ; 
 int /*<<< orphan*/  esp_input_done_esn ; 
 int /*<<< orphan*/  esp_input_restore_header (struct sk_buff*) ; 
 int /*<<< orphan*/  esp_input_set_header (struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct scatterlist* esp_req_sg (struct crypto_aead*,struct aead_request*) ; 
 int /*<<< orphan*/ * esp_tmp_iv (struct crypto_aead*,void*,int) ; 
 struct aead_request* esp_tmp_req (struct crypto_aead*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * esp_tmp_seqhi (void*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 int skb_cow_data (struct sk_buff*,int /*<<< orphan*/ ,struct sk_buff**) ; 
 int /*<<< orphan*/  skb_has_frag_list (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_nonlinear (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int skb_to_sgvec (struct sk_buff*,struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int esp6_input(struct xfrm_state *x, struct sk_buff *skb)
{
	struct crypto_aead *aead = x->data;
	struct aead_request *req;
	struct sk_buff *trailer;
	int ivlen = crypto_aead_ivsize(aead);
	int elen = skb->len - sizeof(struct ip_esp_hdr) - ivlen;
	int nfrags;
	int assoclen;
	int seqhilen;
	int ret = 0;
	void *tmp;
	__be32 *seqhi;
	u8 *iv;
	struct scatterlist *sg;

	if (!pskb_may_pull(skb, sizeof(struct ip_esp_hdr) + ivlen)) {
		ret = -EINVAL;
		goto out;
	}

	if (elen <= 0) {
		ret = -EINVAL;
		goto out;
	}

	assoclen = sizeof(struct ip_esp_hdr);
	seqhilen = 0;

	if (x->props.flags & XFRM_STATE_ESN) {
		seqhilen += sizeof(__be32);
		assoclen += seqhilen;
	}

	if (!skb_cloned(skb)) {
		if (!skb_is_nonlinear(skb)) {
			nfrags = 1;

			goto skip_cow;
		} else if (!skb_has_frag_list(skb)) {
			nfrags = skb_shinfo(skb)->nr_frags;
			nfrags++;

			goto skip_cow;
		}
	}

	nfrags = skb_cow_data(skb, 0, &trailer);
	if (nfrags < 0) {
		ret = -EINVAL;
		goto out;
	}

skip_cow:
	ret = -ENOMEM;
	tmp = esp_alloc_tmp(aead, nfrags, seqhilen);
	if (!tmp)
		goto out;

	ESP_SKB_CB(skb)->tmp = tmp;
	seqhi = esp_tmp_seqhi(tmp);
	iv = esp_tmp_iv(aead, tmp, seqhilen);
	req = esp_tmp_req(aead, iv);
	sg = esp_req_sg(aead, req);

	esp_input_set_header(skb, seqhi);

	sg_init_table(sg, nfrags);
	ret = skb_to_sgvec(skb, sg, 0, skb->len);
	if (unlikely(ret < 0)) {
		kfree(tmp);
		goto out;
	}

	skb->ip_summed = CHECKSUM_NONE;

	if ((x->props.flags & XFRM_STATE_ESN))
		aead_request_set_callback(req, 0, esp_input_done_esn, skb);
	else
		aead_request_set_callback(req, 0, esp_input_done, skb);

	aead_request_set_crypt(req, sg, sg, elen + ivlen, iv);
	aead_request_set_ad(req, assoclen);

	ret = crypto_aead_decrypt(req);
	if (ret == -EINPROGRESS)
		goto out;

	if ((x->props.flags & XFRM_STATE_ESN))
		esp_input_restore_header(skb);

	ret = esp6_input_done2(skb, ret);

out:
	return ret;
}