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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ci_hdrc_remove_device (struct platform_device*) ; 
 struct platform_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ci_hdrc_zevio_remove(struct platform_device *pdev)
{
	struct platform_device *ci_pdev = platform_get_drvdata(pdev);

	ci_hdrc_remove_device(ci_pdev);

	return 0;
}