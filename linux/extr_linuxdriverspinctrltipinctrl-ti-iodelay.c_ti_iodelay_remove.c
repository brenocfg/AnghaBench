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
struct ti_iodelay_device {scalar_t__ pctl; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pinctrl_unregister (scalar_t__) ; 
 struct ti_iodelay_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  ti_iodelay_pinconf_deinit_dev (struct ti_iodelay_device*) ; 

__attribute__((used)) static int ti_iodelay_remove(struct platform_device *pdev)
{
	struct ti_iodelay_device *iod = platform_get_drvdata(pdev);

	if (!iod)
		return 0;

	if (iod->pctl)
		pinctrl_unregister(iod->pctl);

	ti_iodelay_pinconf_deinit_dev(iod);

	/* Expect other allocations to be freed by devm */

	return 0;
}