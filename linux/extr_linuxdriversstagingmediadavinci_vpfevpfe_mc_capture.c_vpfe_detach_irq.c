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
struct vpfe_device {int /*<<< orphan*/  imp_dma_irq; int /*<<< orphan*/  ccdc_irq1; int /*<<< orphan*/  ccdc_irq0; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct vpfe_device*) ; 

__attribute__((used)) static void vpfe_detach_irq(struct vpfe_device *vpfe_dev)
{
	free_irq(vpfe_dev->ccdc_irq0, vpfe_dev);
	free_irq(vpfe_dev->ccdc_irq1, vpfe_dev);
	free_irq(vpfe_dev->imp_dma_irq, vpfe_dev);
}