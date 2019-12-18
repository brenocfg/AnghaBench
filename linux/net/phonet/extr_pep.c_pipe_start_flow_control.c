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
struct sock {int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;} ;
struct pep_sock {int /*<<< orphan*/  tx_credits; int /*<<< orphan*/  tx_fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int /*<<< orphan*/  pipe_grant_credits (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pn_flow_safe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void pipe_start_flow_control(struct sock *sk)
{
	struct pep_sock *pn = pep_sk(sk);

	if (!pn_flow_safe(pn->tx_fc)) {
		atomic_set(&pn->tx_credits, 1);
		sk->sk_write_space(sk);
	}
	pipe_grant_credits(sk, GFP_ATOMIC);
}