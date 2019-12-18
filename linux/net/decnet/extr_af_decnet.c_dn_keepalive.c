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
struct dn_scp {int /*<<< orphan*/  other_xmit_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DN_NOCHANGE ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 int /*<<< orphan*/  dn_nsp_send_link (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dn_keepalive(struct sock *sk)
{
	struct dn_scp *scp = DN_SK(sk);

	/*
	 * By checking the other_data transmit queue is empty
	 * we are double checking that we are not sending too
	 * many of these keepalive frames.
	 */
	if (skb_queue_empty(&scp->other_xmit_queue))
		dn_nsp_send_link(sk, DN_NOCHANGE, 0);
}