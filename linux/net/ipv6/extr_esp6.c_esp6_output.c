#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int /*<<< orphan*/  spi; } ;
struct xfrm_state {TYPE_1__ id; scalar_t__ tfcpad; struct crypto_aead* data; } ;
struct xfrm_dst {int /*<<< orphan*/  child_mtu_cached; } ;
struct sk_buff {scalar_t__ len; } ;
struct ip_esp_hdr {int /*<<< orphan*/  seq_no; int /*<<< orphan*/  spi; } ;
struct esp_info {int inplace; int tfclen; int clen; int plen; int tailen; scalar_t__ nfrags; int /*<<< orphan*/  seqno; int /*<<< orphan*/  proto; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_6__ {scalar_t__ hi; scalar_t__ low; } ;
struct TYPE_7__ {TYPE_2__ output; } ;
struct TYPE_8__ {TYPE_3__ seq; } ;

/* Variables and functions */
 void* ALIGN (int,int) ; 
 int /*<<< orphan*/  IPPROTO_ESP ; 
 TYPE_4__* XFRM_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int crypto_aead_authsize (struct crypto_aead*) ; 
 int crypto_aead_blocksize (struct crypto_aead*) ; 
 scalar_t__ esp6_output_head (struct xfrm_state*,struct sk_buff*,struct esp_info*) ; 
 int esp6_output_tail (struct xfrm_state*,struct sk_buff*,struct esp_info*) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 struct ip_esp_hdr* ip_esp_hdr (struct sk_buff*) ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_state_mtu (struct xfrm_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esp6_output(struct xfrm_state *x, struct sk_buff *skb)
{
	int alen;
	int blksize;
	struct ip_esp_hdr *esph;
	struct crypto_aead *aead;
	struct esp_info esp;

	esp.inplace = true;

	esp.proto = *skb_mac_header(skb);
	*skb_mac_header(skb) = IPPROTO_ESP;

	/* skb is pure payload to encrypt */

	aead = x->data;
	alen = crypto_aead_authsize(aead);

	esp.tfclen = 0;
	if (x->tfcpad) {
		struct xfrm_dst *dst = (struct xfrm_dst *)skb_dst(skb);
		u32 padto;

		padto = min(x->tfcpad, xfrm_state_mtu(x, dst->child_mtu_cached));
		if (skb->len < padto)
			esp.tfclen = padto - skb->len;
	}
	blksize = ALIGN(crypto_aead_blocksize(aead), 4);
	esp.clen = ALIGN(skb->len + 2 + esp.tfclen, blksize);
	esp.plen = esp.clen - skb->len - esp.tfclen;
	esp.tailen = esp.tfclen + esp.plen + alen;

	esp.nfrags = esp6_output_head(x, skb, &esp);
	if (esp.nfrags < 0)
		return esp.nfrags;

	esph = ip_esp_hdr(skb);
	esph->spi = x->id.spi;

	esph->seq_no = htonl(XFRM_SKB_CB(skb)->seq.output.low);
	esp.seqno = cpu_to_be64(XFRM_SKB_CB(skb)->seq.output.low +
			    ((u64)XFRM_SKB_CB(skb)->seq.output.hi << 32));

	skb_push(skb, -skb_network_offset(skb));

	return esp6_output_tail(x, skb, &esp);
}