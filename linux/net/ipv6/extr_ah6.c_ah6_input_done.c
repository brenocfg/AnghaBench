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
struct ip_auth_hdr {int nexthdr; } ;
struct crypto_async_request {struct sk_buff* data; } ;
struct ah_data {int /*<<< orphan*/  icv_trunc_len; int /*<<< orphan*/  ahash; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tmp; } ;

/* Variables and functions */
 TYPE_2__* AH_SKB_CB (struct sk_buff*) ; 
 int EBADMSG ; 
 scalar_t__ XFRM_MODE_TUNNEL ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/ * ah_tmp_auth (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ah_tmp_icv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_memneq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ip_auth_hdr* ip_auth_hdr (struct sk_buff*) ; 
 int ipv6_authlen (struct ip_auth_hdr*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_network_header (struct sk_buff*) ; 
 int skb_network_header_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  xfrm_input_resume (struct sk_buff*,int) ; 
 struct xfrm_state* xfrm_input_state (struct sk_buff*) ; 

__attribute__((used)) static void ah6_input_done(struct crypto_async_request *base, int err)
{
	u8 *auth_data;
	u8 *icv;
	u8 *work_iph;
	struct sk_buff *skb = base->data;
	struct xfrm_state *x = xfrm_input_state(skb);
	struct ah_data *ahp = x->data;
	struct ip_auth_hdr *ah = ip_auth_hdr(skb);
	int hdr_len = skb_network_header_len(skb);
	int ah_hlen = ipv6_authlen(ah);

	if (err)
		goto out;

	work_iph = AH_SKB_CB(skb)->tmp;
	auth_data = ah_tmp_auth(work_iph, hdr_len);
	icv = ah_tmp_icv(ahp->ahash, auth_data, ahp->icv_trunc_len);

	err = crypto_memneq(icv, auth_data, ahp->icv_trunc_len) ? -EBADMSG : 0;
	if (err)
		goto out;

	err = ah->nexthdr;

	skb->network_header += ah_hlen;
	memcpy(skb_network_header(skb), work_iph, hdr_len);
	__skb_pull(skb, ah_hlen + hdr_len);
	if (x->props.mode == XFRM_MODE_TUNNEL)
		skb_reset_transport_header(skb);
	else
		skb_set_transport_header(skb, -hdr_len);
out:
	kfree(AH_SKB_CB(skb)->tmp);
	xfrm_input_resume(skb, err);
}