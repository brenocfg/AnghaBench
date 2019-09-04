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
struct vpfe_isif_device {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  isif_remove (struct vpfe_isif_device*,struct platform_device*) ; 

void
vpfe_isif_cleanup(struct vpfe_isif_device *isif, struct platform_device *pdev)
{
	isif_remove(isif, pdev);
}