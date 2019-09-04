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
struct imxdi_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_emerg (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void di_what_is_to_be_done(struct imxdi_dev *imxdi,
				  const char *power_supply)
{
	dev_emerg(&imxdi->pdev->dev, "Please cycle the %s power supply in order to get the DryIce/RTC unit working again\n",
		  power_supply);
}