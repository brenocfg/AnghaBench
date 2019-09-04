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
struct ath10k_ahb {int /*<<< orphan*/ * tcsr_mem; int /*<<< orphan*/ * gcc_mem; int /*<<< orphan*/ * mem; TYPE_1__* pdev; } ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_ahb_clock_deinit (struct ath10k*) ; 
 struct ath10k_ahb* ath10k_ahb_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_ahb_rst_ctrl_deinit (struct ath10k*) ; 
 int /*<<< orphan*/  devm_iounmap (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_ahb_resource_deinit(struct ath10k *ar)
{
	struct ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);
	struct device *dev;

	dev = &ar_ahb->pdev->dev;

	if (ar_ahb->mem)
		devm_iounmap(dev, ar_ahb->mem);

	if (ar_ahb->gcc_mem)
		iounmap(ar_ahb->gcc_mem);

	if (ar_ahb->tcsr_mem)
		iounmap(ar_ahb->tcsr_mem);

	ar_ahb->mem = NULL;
	ar_ahb->gcc_mem = NULL;
	ar_ahb->tcsr_mem = NULL;

	ath10k_ahb_clock_deinit(ar);
	ath10k_ahb_rst_ctrl_deinit(ar);
}