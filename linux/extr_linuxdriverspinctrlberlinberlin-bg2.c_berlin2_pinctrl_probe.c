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
struct of_device_id {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  berlin2_pinctrl_match ; 
 int berlin_pinctrl_probe (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int berlin2_pinctrl_probe(struct platform_device *pdev)
{
	const struct of_device_id *match =
		of_match_device(berlin2_pinctrl_match, &pdev->dev);

	return berlin_pinctrl_probe(pdev, match->data);
}