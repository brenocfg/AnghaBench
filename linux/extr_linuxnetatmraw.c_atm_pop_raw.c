#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;int /*<<< orphan*/  sk_wmem_alloc; } ;
struct sk_buff {int dummy; } ;
struct atm_vcc {int /*<<< orphan*/  vci; } ;
struct TYPE_2__ {int /*<<< orphan*/  acct_truesize; } ;

/* Variables and functions */
 TYPE_1__* ATM_SKB (struct sk_buff*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_sub_and_test (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sock* sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  sk_wmem_alloc_get (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void atm_pop_raw(struct atm_vcc *vcc, struct sk_buff *skb)
{
	struct sock *sk = sk_atm(vcc);

	pr_debug("(%d) %d -= %d\n",
		 vcc->vci, sk_wmem_alloc_get(sk), ATM_SKB(skb)->acct_truesize);
	WARN_ON(refcount_sub_and_test(ATM_SKB(skb)->acct_truesize, &sk->sk_wmem_alloc));
	dev_kfree_skb_any(skb);
	sk->sk_write_space(sk);
}