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
struct ccid3_hc_tx_sock {int tx_state; } ;
typedef  enum ccid3_hc_tx_states { ____Placeholder_ccid3_hc_tx_states } ccid3_hc_tx_states ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ccid3_hc_tx_sock* ccid3_hc_tx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid3_pr_debug (char*,int /*<<< orphan*/ ,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccid3_tx_state_name (int) ; 
 int /*<<< orphan*/  dccp_role (struct sock*) ; 

__attribute__((used)) static void ccid3_hc_tx_set_state(struct sock *sk,
				  enum ccid3_hc_tx_states state)
{
	struct ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	enum ccid3_hc_tx_states oldstate = hc->tx_state;

	ccid3_pr_debug("%s(%p) %-8.8s -> %s\n",
		       dccp_role(sk), sk, ccid3_tx_state_name(oldstate),
		       ccid3_tx_state_name(state));
	WARN_ON(state == oldstate);
	hc->tx_state = state;
}