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
struct vpfe_device {int /*<<< orphan*/  ccdc_irq0; int /*<<< orphan*/  ccdc_irq1; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  imp_dma_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct vpfe_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct vpfe_device*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vpfe_imp_dma_isr ; 
 int /*<<< orphan*/  vpfe_isr ; 
 int /*<<< orphan*/  vpfe_vdint1_isr ; 

__attribute__((used)) static int vpfe_attach_irq(struct vpfe_device *vpfe_dev)
{
	int ret;

	ret = request_irq(vpfe_dev->ccdc_irq0, vpfe_isr, 0,
			  "vpfe_capture0", vpfe_dev);
	if (ret < 0) {
		v4l2_err(&vpfe_dev->v4l2_dev,
			"Error: requesting VINT0 interrupt\n");
		return ret;
	}

	ret = request_irq(vpfe_dev->ccdc_irq1, vpfe_vdint1_isr, 0,
			  "vpfe_capture1", vpfe_dev);
	if (ret < 0) {
		v4l2_err(&vpfe_dev->v4l2_dev,
			"Error: requesting VINT1 interrupt\n");
		free_irq(vpfe_dev->ccdc_irq0, vpfe_dev);
		return ret;
	}

	ret = request_irq(vpfe_dev->imp_dma_irq, vpfe_imp_dma_isr,
			  0, "Imp_Sdram_Irq", vpfe_dev);
	if (ret < 0) {
		v4l2_err(&vpfe_dev->v4l2_dev,
			 "Error: requesting IMP IRQ interrupt\n");
		free_irq(vpfe_dev->ccdc_irq1, vpfe_dev);
		free_irq(vpfe_dev->ccdc_irq0, vpfe_dev);
		return ret;
	}

	return 0;
}