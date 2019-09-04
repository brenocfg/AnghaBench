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
struct ath10k_ahb {int /*<<< orphan*/ * rtc_clk; int /*<<< orphan*/ * ref_clk; int /*<<< orphan*/ * cmd_clk; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 struct ath10k_ahb* ath10k_ahb_priv (struct ath10k*) ; 

__attribute__((used)) static void ath10k_ahb_clock_deinit(struct ath10k *ar)
{
	struct ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);

	ar_ahb->cmd_clk = NULL;
	ar_ahb->ref_clk = NULL;
	ar_ahb->rtc_clk = NULL;
}