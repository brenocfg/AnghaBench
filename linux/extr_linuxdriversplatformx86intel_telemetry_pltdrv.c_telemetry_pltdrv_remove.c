#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  regmap; } ;
struct TYPE_6__ {TYPE_2__ ioss_config; TYPE_1__ pss_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  telemetry_clear_pltdata () ; 
 TYPE_3__* telm_conf ; 

__attribute__((used)) static int telemetry_pltdrv_remove(struct platform_device *pdev)
{
	telemetry_clear_pltdata();
	iounmap(telm_conf->pss_config.regmap);
	iounmap(telm_conf->ioss_config.regmap);

	return 0;
}