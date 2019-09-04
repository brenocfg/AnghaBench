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
struct tsens_device {TYPE_1__* ops; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct tsens_device*) ;} ;

/* Variables and functions */
 struct tsens_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct tsens_device*) ; 

__attribute__((used)) static int tsens_remove(struct platform_device *pdev)
{
	struct tsens_device *tmdev = platform_get_drvdata(pdev);

	if (tmdev->ops->disable)
		tmdev->ops->disable(tmdev);

	return 0;
}