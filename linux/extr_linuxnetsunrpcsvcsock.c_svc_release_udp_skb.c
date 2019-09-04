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
struct svc_rqst {struct sk_buff* rq_xprt_ctxt; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dprintk (char*,struct svc_rqst*,struct sk_buff*) ; 

__attribute__((used)) static void svc_release_udp_skb(struct svc_rqst *rqstp)
{
	struct sk_buff *skb = rqstp->rq_xprt_ctxt;

	if (skb) {
		rqstp->rq_xprt_ctxt = NULL;

		dprintk("svc: service %p, releasing skb %p\n", rqstp, skb);
		consume_skb(skb);
	}
}