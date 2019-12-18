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
struct socket_smack {struct smack_known* smk_out; } ;
struct sock {struct socket_smack* sk_security; } ;
struct smack_known {int /*<<< orphan*/  smk_secid; } ;
struct sk_buff {int /*<<< orphan*/  secmark; } ;
struct nf_hook_state {int dummy; } ;

/* Variables and functions */
 unsigned int NF_ACCEPT ; 
 struct sock* skb_to_full_sk (struct sk_buff*) ; 

__attribute__((used)) static unsigned int smack_ipv4_output(void *priv,
					struct sk_buff *skb,
					const struct nf_hook_state *state)
{
	struct sock *sk = skb_to_full_sk(skb);
	struct socket_smack *ssp;
	struct smack_known *skp;

	if (sk && sk->sk_security) {
		ssp = sk->sk_security;
		skp = ssp->smk_out;
		skb->secmark = skp->smk_secid;
	}

	return NF_ACCEPT;
}