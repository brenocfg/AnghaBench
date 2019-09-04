#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct ath10k_ahb {void* rtc_clk; void* ref_clk; void* cmd_clk; TYPE_1__* pdev; } ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR_OR_NULL (void*) ; 
 int PTR_ERR (void*) ; 
 struct ath10k_ahb* ath10k_ahb_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 void* devm_clk_get (struct device*,char*) ; 

__attribute__((used)) static int ath10k_ahb_clock_init(struct ath10k *ar)
{
	struct ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);
	struct device *dev;

	dev = &ar_ahb->pdev->dev;

	ar_ahb->cmd_clk = devm_clk_get(dev, "wifi_wcss_cmd");
	if (IS_ERR_OR_NULL(ar_ahb->cmd_clk)) {
		ath10k_err(ar, "failed to get cmd clk: %ld\n",
			   PTR_ERR(ar_ahb->cmd_clk));
		return ar_ahb->cmd_clk ? PTR_ERR(ar_ahb->cmd_clk) : -ENODEV;
	}

	ar_ahb->ref_clk = devm_clk_get(dev, "wifi_wcss_ref");
	if (IS_ERR_OR_NULL(ar_ahb->ref_clk)) {
		ath10k_err(ar, "failed to get ref clk: %ld\n",
			   PTR_ERR(ar_ahb->ref_clk));
		return ar_ahb->ref_clk ? PTR_ERR(ar_ahb->ref_clk) : -ENODEV;
	}

	ar_ahb->rtc_clk = devm_clk_get(dev, "wifi_wcss_rtc");
	if (IS_ERR_OR_NULL(ar_ahb->rtc_clk)) {
		ath10k_err(ar, "failed to get rtc clk: %ld\n",
			   PTR_ERR(ar_ahb->rtc_clk));
		return ar_ahb->rtc_clk ? PTR_ERR(ar_ahb->rtc_clk) : -ENODEV;
	}

	return 0;
}