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
struct ath10k_ahb {void* cpu_init_rst; void* radio_srif_rst; void* radio_warm_rst; void* radio_cold_rst; void* core_cold_rst; TYPE_1__* pdev; } ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 struct ath10k_ahb* ath10k_ahb_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 void* devm_reset_control_get_exclusive (struct device*,char*) ; 

__attribute__((used)) static int ath10k_ahb_rst_ctrl_init(struct ath10k *ar)
{
	struct ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);
	struct device *dev;

	dev = &ar_ahb->pdev->dev;

	ar_ahb->core_cold_rst = devm_reset_control_get_exclusive(dev,
								 "wifi_core_cold");
	if (IS_ERR(ar_ahb->core_cold_rst)) {
		ath10k_err(ar, "failed to get core cold rst ctrl: %ld\n",
			   PTR_ERR(ar_ahb->core_cold_rst));
		return PTR_ERR(ar_ahb->core_cold_rst);
	}

	ar_ahb->radio_cold_rst = devm_reset_control_get_exclusive(dev,
								  "wifi_radio_cold");
	if (IS_ERR(ar_ahb->radio_cold_rst)) {
		ath10k_err(ar, "failed to get radio cold rst ctrl: %ld\n",
			   PTR_ERR(ar_ahb->radio_cold_rst));
		return PTR_ERR(ar_ahb->radio_cold_rst);
	}

	ar_ahb->radio_warm_rst = devm_reset_control_get_exclusive(dev,
								  "wifi_radio_warm");
	if (IS_ERR(ar_ahb->radio_warm_rst)) {
		ath10k_err(ar, "failed to get radio warm rst ctrl: %ld\n",
			   PTR_ERR(ar_ahb->radio_warm_rst));
		return PTR_ERR(ar_ahb->radio_warm_rst);
	}

	ar_ahb->radio_srif_rst = devm_reset_control_get_exclusive(dev,
								  "wifi_radio_srif");
	if (IS_ERR(ar_ahb->radio_srif_rst)) {
		ath10k_err(ar, "failed to get radio srif rst ctrl: %ld\n",
			   PTR_ERR(ar_ahb->radio_srif_rst));
		return PTR_ERR(ar_ahb->radio_srif_rst);
	}

	ar_ahb->cpu_init_rst = devm_reset_control_get_exclusive(dev,
								"wifi_cpu_init");
	if (IS_ERR(ar_ahb->cpu_init_rst)) {
		ath10k_err(ar, "failed to get cpu init rst ctrl: %ld\n",
			   PTR_ERR(ar_ahb->cpu_init_rst));
		return PTR_ERR(ar_ahb->cpu_init_rst);
	}

	return 0;
}