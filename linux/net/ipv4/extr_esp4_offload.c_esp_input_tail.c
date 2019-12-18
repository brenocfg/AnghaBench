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
struct xfrm_state {struct crypto_aead* data; } ;
struct xfrm_offload {int flags; } ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct ip_esp_hdr {int dummy; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int CRYPTO_DONE ; 
 int EINVAL ; 
 scalar_t__ crypto_aead_ivsize (struct crypto_aead*) ; 
 int esp_input_done2 (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 struct xfrm_offload* xfrm_offload (struct sk_buff*) ; 

__attribute__((used)) static int esp_input_tail(struct xfrm_state *x, struct sk_buff *skb)
{
	struct crypto_aead *aead = x->data;
	struct xfrm_offload *xo = xfrm_offload(skb);

	if (!pskb_may_pull(skb, sizeof(struct ip_esp_hdr) + crypto_aead_ivsize(aead)))
		return -EINVAL;

	if (!(xo->flags & CRYPTO_DONE))
		skb->ip_summed = CHECKSUM_NONE;

	return esp_input_done2(skb, 0);
}