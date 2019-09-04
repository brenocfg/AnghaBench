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
struct TYPE_2__ {void* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kirkwood_pinctrl_of_match ; 
 int mvebu_pinctrl_simple_mmio_probe (struct platform_device*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int kirkwood_pinctrl_probe(struct platform_device *pdev)
{
	const struct of_device_id *match =
		of_match_device(kirkwood_pinctrl_of_match, &pdev->dev);

	pdev->dev.platform_data = (void *)match->data;

	return mvebu_pinctrl_simple_mmio_probe(pdev);
}