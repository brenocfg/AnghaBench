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
struct ath10k_ahb {int /*<<< orphan*/  cmd_clk; int /*<<< orphan*/  ref_clk; int /*<<< orphan*/  rtc_clk; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 struct ath10k_ahb* ath10k_ahb_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,...) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_ahb_clock_enable(struct ath10k *ar)
{
	struct ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);
	int ret;

	if (IS_ERR_OR_NULL(ar_ahb->cmd_clk) ||
	    IS_ERR_OR_NULL(ar_ahb->ref_clk) ||
	    IS_ERR_OR_NULL(ar_ahb->rtc_clk)) {
		ath10k_err(ar, "clock(s) is/are not initialized\n");
		ret = -EIO;
		goto out;
	}

	ret = clk_prepare_enable(ar_ahb->cmd_clk);
	if (ret) {
		ath10k_err(ar, "failed to enable cmd clk: %d\n", ret);
		goto out;
	}

	ret = clk_prepare_enable(ar_ahb->ref_clk);
	if (ret) {
		ath10k_err(ar, "failed to enable ref clk: %d\n", ret);
		goto err_cmd_clk_disable;
	}

	ret = clk_prepare_enable(ar_ahb->rtc_clk);
	if (ret) {
		ath10k_err(ar, "failed to enable rtc clk: %d\n", ret);
		goto err_ref_clk_disable;
	}

	return 0;

err_ref_clk_disable:
	clk_disable_unprepare(ar_ahb->ref_clk);

err_cmd_clk_disable:
	clk_disable_unprepare(ar_ahb->cmd_clk);

out:
	return ret;
}