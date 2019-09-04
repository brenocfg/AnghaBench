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

/* Variables and functions */
 int /*<<< orphan*/  asoc_idma_platform ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ idma_irq ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asoc_idma_platform_probe(struct platform_device *pdev)
{
	idma_irq = platform_get_irq(pdev, 0);
	if (idma_irq < 0)
		return idma_irq;

	return devm_snd_soc_register_component(&pdev->dev, &asoc_idma_platform,
					       NULL, 0);
}