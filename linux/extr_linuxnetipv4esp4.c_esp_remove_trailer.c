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
typedef  int u8 ;
struct xfrm_state {struct crypto_aead* data; } ;
struct xfrm_offload {int flags; int proto; } ;
struct sk_buff {int len; scalar_t__ ip_summed; int /*<<< orphan*/  csum; } ;
struct ip_esp_hdr {int dummy; } ;
struct crypto_aead {int dummy; } ;
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ CHECKSUM_COMPLETE ; 
 int EINVAL ; 
 int XFRM_ESP_NO_TRAILER ; 
 int crypto_aead_authsize (struct crypto_aead*) ; 
 int crypto_aead_ivsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  csum_block_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,int,int) ; 
 int /*<<< orphan*/  pskb_trim (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,int,int*,int) ; 
 struct xfrm_state* xfrm_input_state (struct sk_buff*) ; 
 struct xfrm_offload* xfrm_offload (struct sk_buff*) ; 

__attribute__((used)) static inline int esp_remove_trailer(struct sk_buff *skb)
{
	struct xfrm_state *x = xfrm_input_state(skb);
	struct xfrm_offload *xo = xfrm_offload(skb);
	struct crypto_aead *aead = x->data;
	int alen, hlen, elen;
	int padlen, trimlen;
	__wsum csumdiff;
	u8 nexthdr[2];
	int ret;

	alen = crypto_aead_authsize(aead);
	hlen = sizeof(struct ip_esp_hdr) + crypto_aead_ivsize(aead);
	elen = skb->len - hlen;

	if (xo && (xo->flags & XFRM_ESP_NO_TRAILER)) {
		ret = xo->proto;
		goto out;
	}

	if (skb_copy_bits(skb, skb->len - alen - 2, nexthdr, 2))
		BUG();

	ret = -EINVAL;
	padlen = nexthdr[0];
	if (padlen + 2 + alen >= elen) {
		net_dbg_ratelimited("ipsec esp packet is garbage padlen=%d, elen=%d\n",
				    padlen + 2, elen - alen);
		goto out;
	}

	trimlen = alen + padlen + 2;
	if (skb->ip_summed == CHECKSUM_COMPLETE) {
		csumdiff = skb_checksum(skb, skb->len - trimlen, trimlen, 0);
		skb->csum = csum_block_sub(skb->csum, csumdiff,
					   skb->len - trimlen);
	}
	pskb_trim(skb, skb->len - trimlen);

	ret = nexthdr[1];

out:
	return ret;
}