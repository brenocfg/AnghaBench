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
struct TYPE_5__ {scalar_t__ dev; } ;
struct TYPE_4__ {scalar_t__ spi; } ;
struct xfrm_state {TYPE_2__ xso; TYPE_1__ id; struct crypto_aead* data; } ;
struct xfrm_offload {int /*<<< orphan*/  flags; } ;
struct sk_buff {int encap_hdr_csum; scalar_t__ dev; } ;
struct sec_path {int len; struct xfrm_state** xvec; } ;
struct ip_esp_hdr {scalar_t__ spi; } ;
struct crypto_aead {int dummy; } ;
typedef  int netdev_features_t ;
struct TYPE_6__ {int gso_type; } ;

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
 struct sec_path* skb_sec_path (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 struct sk_buff* xfrm6_outer_mode_gso_segment (struct xfrm_state*,struct sk_buff*,int) ; 
 struct xfrm_offload* xfrm_offload (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *esp6_gso_segment(struct sk_buff *skb,
				        netdev_features_t features)
{
	struct xfrm_state *x;
	struct ip_esp_hdr *esph;
	struct crypto_aead *aead;
	netdev_features_t esp_features = features;
	struct xfrm_offload *xo = xfrm_offload(skb);
	struct sec_path *sp;

	if (!xo)
		return ERR_PTR(-EINVAL);

	if (!(skb_shinfo(skb)->gso_type & SKB_GSO_ESP))
		return ERR_PTR(-EINVAL);

	sp = skb_sec_path(skb);
	x = sp->xvec[sp->len - 1];
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

	return xfrm6_outer_mode_gso_segment(x, skb, esp_features);
}