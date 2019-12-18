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
struct ccid3_hc_rx_sock {int /*<<< orphan*/  rx_li_hist; int /*<<< orphan*/  rx_hist; } ;

/* Variables and functions */
 struct ccid3_hc_rx_sock* ccid3_hc_rx_sk (struct sock*) ; 
 int /*<<< orphan*/  tfrc_lh_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfrc_rx_hist_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccid3_hc_rx_exit(struct sock *sk)
{
	struct ccid3_hc_rx_sock *hc = ccid3_hc_rx_sk(sk);

	tfrc_rx_hist_purge(&hc->rx_hist);
	tfrc_lh_cleanup(&hc->rx_li_hist);
}