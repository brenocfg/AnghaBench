#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ mode; } ;
struct xfrm_state {TYPE_1__ props; struct ah_data* data; } ;
struct sk_buff {int network_header; } ;
struct iphdr {int dummy; } ;
struct ip_auth_hdr {int hdrlen; int nexthdr; } ;
struct crypto_async_request {struct sk_buff* data; } ;
struct ah_data {int /*<<< orphan*/  icv_trunc_len; int /*<<< orphan*/  ahash; } ;
struct TYPE_4__ {struct iphdr* tmp; } ;

/* Variables and functions */
 TYPE_2__* AH_SKB_CB (struct sk_buff*) ; 
 int EBADMSG ; 
 scalar_t__ XFRM_MODE_TUNNEL ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/ * ah_tmp_auth (struct iphdr*,int) ; 
 int /*<<< orphan*/ * ah_tmp_icv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_memneq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ip_auth_hdr* ip_auth_hdr (struct sk_buff*) ; 
 int ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (struct iphdr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct iphdr*,int) ; 
 int /*<<< orphan*/  skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  xfrm_input_resume (struct sk_buff*,int) ; 
 struct xfrm_state* xfrm_input_state (struct sk_buff*) ; 

__attribute__((used)) static void ah_input_done(struct crypto_async_request *base, int err)
{
	u8 *auth_data;
	u8 *icv;
	struct iphdr *work_iph;
	struct sk_buff *skb = base->data;
	struct xfrm_state *x = xfrm_input_state(skb);
	struct ah_data *ahp = x->data;
	struct ip_auth_hdr *ah = ip_auth_hdr(skb);
	int ihl = ip_hdrlen(skb);
	int ah_hlen = (ah->hdrlen + 2) << 2;

	if (err)
		goto out;

	work_iph = AH_SKB_CB(skb)->tmp;
	auth_data = ah_tmp_auth(work_iph, ihl);
	icv = ah_tmp_icv(ahp->ahash, auth_data, ahp->icv_trunc_len);

	err = crypto_memneq(icv, auth_data, ahp->icv_trunc_len) ? -EBADMSG : 0;
	if (err)
		goto out;

	err = ah->nexthdr;

	skb->network_header += ah_hlen;
	memcpy(skb_network_header(skb), work_iph, ihl);
	__skb_pull(skb, ah_hlen + ihl);

	if (x->props.mode == XFRM_MODE_TUNNEL)
		skb_reset_transport_header(skb);
	else
		skb_set_transport_header(skb, -ihl);
out:
	kfree(AH_SKB_CB(skb)->tmp);
	xfrm_input_resume(skb, err);
}