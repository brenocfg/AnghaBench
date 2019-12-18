#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ a4; } ;
typedef  TYPE_3__ xfrm_address_t ;
struct TYPE_6__ {scalar_t__ a4; } ;
struct TYPE_7__ {scalar_t__ mode; TYPE_1__ saddr; } ;
struct xfrm_state {TYPE_2__ props; struct xfrm_encap_tmpl* encap; struct crypto_aead* data; } ;
struct xfrm_offload {int flags; } ;
struct xfrm_encap_tmpl {scalar_t__ encap_sport; } ;
struct udphdr {scalar_t__ source; } ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct iphdr {int ihl; scalar_t__ saddr; } ;
struct ip_esp_hdr {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  tmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int CRYPTO_DONE ; 
 int EINVAL ; 
 TYPE_5__* ESP_SKB_CB (struct sk_buff*) ; 
 int IPPROTO_NONE ; 
 scalar_t__ XFRM_MODE_TRANSPORT ; 
 scalar_t__ XFRM_MODE_TUNNEL ; 
 int crypto_aead_ivsize (struct crypto_aead*) ; 
 int esp_remove_trailer (struct sk_buff*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  km_new_mapping (struct xfrm_state*,TYPE_3__*,scalar_t__) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull_rcsum (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 
 struct xfrm_state* xfrm_input_state (struct sk_buff*) ; 
 struct xfrm_offload* xfrm_offload (struct sk_buff*) ; 

int esp_input_done2(struct sk_buff *skb, int err)
{
	const struct iphdr *iph;
	struct xfrm_state *x = xfrm_input_state(skb);
	struct xfrm_offload *xo = xfrm_offload(skb);
	struct crypto_aead *aead = x->data;
	int hlen = sizeof(struct ip_esp_hdr) + crypto_aead_ivsize(aead);
	int ihl;

	if (!xo || (xo && !(xo->flags & CRYPTO_DONE)))
		kfree(ESP_SKB_CB(skb)->tmp);

	if (unlikely(err))
		goto out;

	err = esp_remove_trailer(skb);
	if (unlikely(err < 0))
		goto out;

	iph = ip_hdr(skb);
	ihl = iph->ihl * 4;

	if (x->encap) {
		struct xfrm_encap_tmpl *encap = x->encap;
		struct udphdr *uh = (void *)(skb_network_header(skb) + ihl);

		/*
		 * 1) if the NAT-T peer's IP or port changed then
		 *    advertize the change to the keying daemon.
		 *    This is an inbound SA, so just compare
		 *    SRC ports.
		 */
		if (iph->saddr != x->props.saddr.a4 ||
		    uh->source != encap->encap_sport) {
			xfrm_address_t ipaddr;

			ipaddr.a4 = iph->saddr;
			km_new_mapping(x, &ipaddr, uh->source);

			/* XXX: perhaps add an extra
			 * policy check here, to see
			 * if we should allow or
			 * reject a packet from a
			 * different source
			 * address/port.
			 */
		}

		/*
		 * 2) ignore UDP/TCP checksums in case
		 *    of NAT-T in Transport Mode, or
		 *    perform other post-processing fixes
		 *    as per draft-ietf-ipsec-udp-encaps-06,
		 *    section 3.1.2
		 */
		if (x->props.mode == XFRM_MODE_TRANSPORT)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	}

	skb_pull_rcsum(skb, hlen);
	if (x->props.mode == XFRM_MODE_TUNNEL)
		skb_reset_transport_header(skb);
	else
		skb_set_transport_header(skb, -ihl);

	/* RFC4303: Drop dummy packets without any error */
	if (err == IPPROTO_NONE)
		err = -EINVAL;

out:
	return err;
}