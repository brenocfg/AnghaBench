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
struct intel_sst_drv {int dummy; } ;

/* Variables and functions */
 struct intel_sst_drv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sst_context_cleanup (struct intel_sst_drv*) ; 

__attribute__((used)) static int sst_acpi_remove(struct platform_device *pdev)
{
	struct intel_sst_drv *ctx;

	ctx = platform_get_drvdata(pdev);
	sst_context_cleanup(ctx);
	platform_set_drvdata(pdev, NULL);
	return 0;
}