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
struct vpfe_device {int /*<<< orphan*/  vpfe_resizer; int /*<<< orphan*/  vpfe_ipipe; int /*<<< orphan*/  vpfe_ipipeif; int /*<<< orphan*/  vpfe_isif; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vpfe_ipipe_cleanup (int /*<<< orphan*/ *,struct platform_device*) ; 
 int /*<<< orphan*/  vpfe_ipipeif_cleanup (int /*<<< orphan*/ *,struct platform_device*) ; 
 int /*<<< orphan*/  vpfe_isif_cleanup (int /*<<< orphan*/ *,struct platform_device*) ; 
 int /*<<< orphan*/  vpfe_resizer_cleanup (int /*<<< orphan*/ *,struct platform_device*) ; 

__attribute__((used)) static void vpfe_cleanup_modules(struct vpfe_device *vpfe_dev,
				 struct platform_device *pdev)
{
	vpfe_isif_cleanup(&vpfe_dev->vpfe_isif, pdev);
	vpfe_ipipeif_cleanup(&vpfe_dev->vpfe_ipipeif, pdev);
	vpfe_ipipe_cleanup(&vpfe_dev->vpfe_ipipe, pdev);
	vpfe_resizer_cleanup(&vpfe_dev->vpfe_resizer, pdev);
}