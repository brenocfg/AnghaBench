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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dma_object {int /*<<< orphan*/  irq; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 struct dma_object* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dma_object*) ; 

__attribute__((used)) static int fsl_soc_dma_remove(struct platform_device *pdev)
{
	struct dma_object *dma = dev_get_drvdata(&pdev->dev);

	iounmap(dma->channel);
	irq_dispose_mapping(dma->irq);
	kfree(dma);

	return 0;
}