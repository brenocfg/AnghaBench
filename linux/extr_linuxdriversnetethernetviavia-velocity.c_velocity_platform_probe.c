#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct velocity_info_tbl {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {struct velocity_info_tbl* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_PLATFORM ; 
 int EINVAL ; 
 int irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  velocity_of_ids ; 
 int velocity_probe (TYPE_1__*,int,struct velocity_info_tbl const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int velocity_platform_probe(struct platform_device *pdev)
{
	const struct of_device_id *of_id;
	const struct velocity_info_tbl *info;
	int irq;

	of_id = of_match_device(velocity_of_ids, &pdev->dev);
	if (!of_id)
		return -EINVAL;
	info = of_id->data;

	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	if (!irq)
		return -EINVAL;

	return velocity_probe(&pdev->dev, irq, info, BUS_PLATFORM);
}