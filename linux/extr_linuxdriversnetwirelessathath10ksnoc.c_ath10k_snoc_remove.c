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
struct platform_device {int dummy; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_SNOC ; 
 int /*<<< orphan*/  ath10k_core_destroy (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_core_unregister (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_hw_power_off (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_snoc_free_irq (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_snoc_release_resource (struct ath10k*) ; 
 struct ath10k* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ath10k_snoc_remove(struct platform_device *pdev)
{
	struct ath10k *ar = platform_get_drvdata(pdev);

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc remove\n");
	ath10k_core_unregister(ar);
	ath10k_hw_power_off(ar);
	ath10k_snoc_free_irq(ar);
	ath10k_snoc_release_resource(ar);
	ath10k_core_destroy(ar);

	return 0;
}