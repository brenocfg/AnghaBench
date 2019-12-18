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
struct ccid3_hc_tx_sock {int /*<<< orphan*/  tx_no_feedback_timer; struct sock* sk; int /*<<< orphan*/ * tx_hist; int /*<<< orphan*/  tx_state; } ;
struct ccid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TFRC_SSTATE_NO_SENT ; 
 int /*<<< orphan*/  ccid3_hc_tx_no_feedback_timer ; 
 struct ccid3_hc_tx_sock* ccid_priv (struct ccid*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccid3_hc_tx_init(struct ccid *ccid, struct sock *sk)
{
	struct ccid3_hc_tx_sock *hc = ccid_priv(ccid);

	hc->tx_state = TFRC_SSTATE_NO_SENT;
	hc->tx_hist  = NULL;
	hc->sk	     = sk;
	timer_setup(&hc->tx_no_feedback_timer,
		    ccid3_hc_tx_no_feedback_timer, 0);
	return 0;
}