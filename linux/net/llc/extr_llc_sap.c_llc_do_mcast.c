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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct llc_sap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  llc_sap_rcv (struct llc_sap*,struct sk_buff*,struct sock*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static void llc_do_mcast(struct llc_sap *sap, struct sk_buff *skb,
			 struct sock **stack, int count)
{
	struct sk_buff *skb1;
	int i;

	for (i = 0; i < count; i++) {
		skb1 = skb_clone(skb, GFP_ATOMIC);
		if (!skb1) {
			sock_put(stack[i]);
			continue;
		}

		llc_sap_rcv(sap, skb1, stack[i]);
		sock_put(stack[i]);
	}
}