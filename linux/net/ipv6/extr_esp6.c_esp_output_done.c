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
struct xfrm_state {int dummy; } ;
struct xfrm_offload {int flags; } ;
struct sk_buff {scalar_t__ data; } ;
struct sec_path {int len; struct xfrm_state** xvec; } ;
struct crypto_async_request {struct sk_buff* data; } ;
struct TYPE_4__ {void* tmp; } ;
struct TYPE_3__ {struct xfrm_state* xfrm; } ;

/* Variables and functions */
 TYPE_2__* ESP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMOUTSTATEPROTOERROR ; 
 int XFRM_DEV_RESUME ; 
 int /*<<< orphan*/  XFRM_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ssg_unref (struct xfrm_state*,void*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  secpath_reset (struct sk_buff*) ; 
 TYPE_1__* skb_dst (struct sk_buff*) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 
 struct sec_path* skb_sec_path (struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm_dev_resume (struct sk_buff*) ; 
 struct xfrm_offload* xfrm_offload (struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm_output_resume (struct sk_buff*,int) ; 
 int /*<<< orphan*/  xs_net (struct xfrm_state*) ; 

__attribute__((used)) static void esp_output_done(struct crypto_async_request *base, int err)
{
	struct sk_buff *skb = base->data;
	struct xfrm_offload *xo = xfrm_offload(skb);
	void *tmp;
	struct xfrm_state *x;

	if (xo && (xo->flags & XFRM_DEV_RESUME)) {
		struct sec_path *sp = skb_sec_path(skb);

		x = sp->xvec[sp->len - 1];
	} else {
		x = skb_dst(skb)->xfrm;
	}

	tmp = ESP_SKB_CB(skb)->tmp;
	esp_ssg_unref(x, tmp);
	kfree(tmp);

	if (xo && (xo->flags & XFRM_DEV_RESUME)) {
		if (err) {
			XFRM_INC_STATS(xs_net(x), LINUX_MIB_XFRMOUTSTATEPROTOERROR);
			kfree_skb(skb);
			return;
		}

		skb_push(skb, skb->data - skb_mac_header(skb));
		secpath_reset(skb);
		xfrm_dev_resume(skb);
	} else {
		xfrm_output_resume(skb, err);
	}
}