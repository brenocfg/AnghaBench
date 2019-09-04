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
struct pnpipehdr {int /*<<< orphan*/  data0; int /*<<< orphan*/  pipe_handle; int /*<<< orphan*/  message_id; scalar_t__ utid; } ;
struct pep_sock {int /*<<< orphan*/  pipe_handle; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAD ; 
 int /*<<< orphan*/  PNS_PIPE_REMOVE_REQ ; 
 struct sk_buff* pep_alloc_skb (struct sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int pn_skb_send (struct sock*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct pnpipehdr* pnp_hdr (struct sk_buff*) ; 

__attribute__((used)) static int pipe_do_remove(struct sock *sk)
{
	struct pep_sock *pn = pep_sk(sk);
	struct pnpipehdr *ph;
	struct sk_buff *skb;

	skb = pep_alloc_skb(sk, NULL, 0, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	ph = pnp_hdr(skb);
	ph->utid = 0;
	ph->message_id = PNS_PIPE_REMOVE_REQ;
	ph->pipe_handle = pn->pipe_handle;
	ph->data0 = PAD;
	return pn_skb_send(sk, skb, NULL);
}