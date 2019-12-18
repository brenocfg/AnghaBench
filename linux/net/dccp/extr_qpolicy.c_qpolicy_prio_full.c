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

/* Variables and functions */
 int /*<<< orphan*/  dccp_qpolicy_drop (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qpolicy_prio_worst_skb (struct sock*) ; 
 scalar_t__ qpolicy_simple_full (struct sock*) ; 

__attribute__((used)) static bool qpolicy_prio_full(struct sock *sk)
{
	if (qpolicy_simple_full(sk))
		dccp_qpolicy_drop(sk, qpolicy_prio_worst_skb(sk));
	return false;
}