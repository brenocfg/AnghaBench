#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_10__ {int /*<<< orphan*/  spi; } ;
struct TYPE_8__ {TYPE_2__* dev; } ;
struct xfrm_state {TYPE_3__ id; struct crypto_aead* data; TYPE_1__ xso; } ;
struct TYPE_11__ {scalar_t__ hi; scalar_t__ low; } ;
struct xfrm_offload {int flags; TYPE_4__ seq; int /*<<< orphan*/  proto; } ;
struct sk_buff {int len; TYPE_2__* dev; } ;
struct ip_esp_hdr {int /*<<< orphan*/  seq_no; int /*<<< orphan*/  spi; } ;
struct esp_info {int inplace; int tfclen; int clen; int plen; int tailen; scalar_t__ nfrags; int /*<<< orphan*/  seqno; struct ip_esp_hdr* esph; int /*<<< orphan*/  proto; } ;
struct crypto_aead {int dummy; } ;
typedef  int netdev_features_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_13__ {int /*<<< orphan*/  tot_len; } ;
struct TYPE_12__ {scalar_t__ gso_segs; } ;
struct TYPE_9__ {int gso_partial_features; } ;

/* Variables and functions */
 void* ALIGN (int,int) ; 
 int CRYPTO_FALLBACK ; 
 int EINVAL ; 
 int NETIF_F_HW_ESP ; 
 int XFRM_GSO_SEGMENT ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int crypto_aead_authsize (struct crypto_aead*) ; 
 int crypto_aead_blocksize (struct crypto_aead*) ; 
 scalar_t__ esp_output_head (struct xfrm_state*,struct sk_buff*,struct esp_info*) ; 
 int esp_output_tail (struct xfrm_state*,struct sk_buff*,struct esp_info*) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int /*<<< orphan*/  htons (int) ; 
 struct ip_esp_hdr* ip_esp_hdr (struct sk_buff*) ; 
 TYPE_6__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_send_check (TYPE_6__*) ; 
 int /*<<< orphan*/  secpath_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_5__* skb_shinfo (struct sk_buff*) ; 
 struct xfrm_offload* xfrm_offload (struct sk_buff*) ; 

__attribute__((used)) static int esp_xmit(struct xfrm_state *x, struct sk_buff *skb,  netdev_features_t features)
{
	int err;
	int alen;
	int blksize;
	struct xfrm_offload *xo;
	struct ip_esp_hdr *esph;
	struct crypto_aead *aead;
	struct esp_info esp;
	bool hw_offload = true;
	__u32 seq;

	esp.inplace = true;

	xo = xfrm_offload(skb);

	if (!xo)
		return -EINVAL;

	if ((!(features & NETIF_F_HW_ESP) &&
	     !(skb->dev->gso_partial_features & NETIF_F_HW_ESP)) ||
	    x->xso.dev != skb->dev) {
		xo->flags |= CRYPTO_FALLBACK;
		hw_offload = false;
	}

	esp.proto = xo->proto;

	/* skb is pure payload to encrypt */

	aead = x->data;
	alen = crypto_aead_authsize(aead);

	esp.tfclen = 0;
	/* XXX: Add support for tfc padding here. */

	blksize = ALIGN(crypto_aead_blocksize(aead), 4);
	esp.clen = ALIGN(skb->len + 2 + esp.tfclen, blksize);
	esp.plen = esp.clen - skb->len - esp.tfclen;
	esp.tailen = esp.tfclen + esp.plen + alen;

	esp.esph = ip_esp_hdr(skb);


	if (!hw_offload || (hw_offload && !skb_is_gso(skb))) {
		esp.nfrags = esp_output_head(x, skb, &esp);
		if (esp.nfrags < 0)
			return esp.nfrags;
	}

	seq = xo->seq.low;

	esph = esp.esph;
	esph->spi = x->id.spi;

	skb_push(skb, -skb_network_offset(skb));

	if (xo->flags & XFRM_GSO_SEGMENT) {
		esph->seq_no = htonl(seq);

		if (!skb_is_gso(skb))
			xo->seq.low++;
		else
			xo->seq.low += skb_shinfo(skb)->gso_segs;
	}

	esp.seqno = cpu_to_be64(seq + ((u64)xo->seq.hi << 32));

	ip_hdr(skb)->tot_len = htons(skb->len);
	ip_send_check(ip_hdr(skb));

	if (hw_offload)
		return 0;

	err = esp_output_tail(x, skb, &esp);
	if (err)
		return err;

	secpath_reset(skb);

	return 0;
}