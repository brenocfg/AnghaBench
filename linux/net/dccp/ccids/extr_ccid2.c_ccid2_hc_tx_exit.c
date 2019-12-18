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
struct ccid2_hc_tx_sock {int tx_seqbufc; int /*<<< orphan*/  tx_av_chunks; int /*<<< orphan*/ * tx_seqbuf; int /*<<< orphan*/  tx_rtotimer; } ;

/* Variables and functions */
 struct ccid2_hc_tx_sock* ccid2_hc_tx_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_ackvec_parsed_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_stop_timer (struct sock*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccid2_hc_tx_exit(struct sock *sk)
{
	struct ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	int i;

	sk_stop_timer(sk, &hc->tx_rtotimer);

	for (i = 0; i < hc->tx_seqbufc; i++)
		kfree(hc->tx_seqbuf[i]);
	hc->tx_seqbufc = 0;
	dccp_ackvec_parsed_cleanup(&hc->tx_av_chunks);
}