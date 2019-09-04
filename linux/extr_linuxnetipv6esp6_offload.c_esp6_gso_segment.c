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
struct TYPE_8__ {scalar_t__ dev; } ;
struct TYPE_7__ {scalar_t__ spi; } ;
struct xfrm_state {TYPE_4__* outer_mode; TYPE_3__ xso; TYPE_2__ id; struct crypto_aead* data; } ;
struct xfrm_offload {int /*<<< orphan*/  flags; } ;
struct sk_buff {int encap_hdr_csum; scalar_t__ dev; TYPE_1__* sp; } ;
struct ip_esp_hdr {scalar_t__ spi; } ;
struct crypto_aead {int dummy; } ;
typedef  int netdev_features_t ;
struct TYPE_10__ {int gso_type; } ;
struct TYPE_9__ {struct sk_buff* (* gso_segment ) (struct xfrm_state*,struct sk_buff*,int) ;} ;
struct TYPE_6__ {int len; struct xfrm_state** xvec; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int NETIF_F_CSUM_MASK ; 
 int NETIF_F_HW_ESP ; 
 int NETIF_F_HW_ESP_TX_CSUM ; 
 int NETIF_F_SG ; 
 int SKB_GSO_ESP ; 
 int /*<<< orphan*/  XFRM_GSO_SEGMENT ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,scalar_t__) ; 
 scalar_t__ crypto_aead_ivsize (struct crypto_aead*) ; 
 struct ip_esp_hdr* ip_esp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 TYPE_5__* skb_shinfo (struct sk_buff*) ; 
 struct sk_buff* stub1 (struct xfrm_state*,struct sk_buff*,int) ; 
 struct xfrm_offload* xfrm_offload (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *esp6_gso_segment(struct sk_buff *skb,
				        netdev_features_t features)
{
	struct xfrm_state *x;
	struct ip_esp_hdr *esph;
	struct crypto_aead *aead;
	netdev_features_t esp_features = features;
	struct xfrm_offload *xo = xfrm_offload(skb);

	if (!xo)
		return ERR_PTR(-EINVAL);

	if (!(skb_shinfo(skb)->gso_type & SKB_GSO_ESP))
		return ERR_PTR(-EINVAL);

	x = skb->sp->xvec[skb->sp->len - 1];
	aead = x->data;
	esph = ip_esp_hdr(skb);

	if (esph->spi != x->id.spi)
		return ERR_PTR(-EINVAL);

	if (!pskb_may_pull(skb, sizeof(*esph) + crypto_aead_ivsize(aead)))
		return ERR_PTR(-EINVAL);

	__skb_pull(skb, sizeof(*esph) + crypto_aead_ivsize(aead));

	skb->encap_hdr_csum = 1;

	if (!(features & NETIF_F_HW_ESP) || x->xso.dev != skb->dev)
		esp_features = features & ~(NETIF_F_SG | NETIF_F_CSUM_MASK);
	else if (!(features & NETIF_F_HW_ESP_TX_CSUM))
		esp_features = features & ~NETIF_F_CSUM_MASK;

	xo->flags |= XFRM_GSO_SEGMENT;

	return x->outer_mode->gso_segment(x, skb, esp_features);
}