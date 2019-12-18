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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int devm_snd_soc_register_card (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  machine_is_mioa701 () ; 
 TYPE_1__ mioa701 ; 

__attribute__((used)) static int mioa701_wm9713_probe(struct platform_device *pdev)
{
	int rc;

	if (!machine_is_mioa701())
		return -ENODEV;

	mioa701.dev = &pdev->dev;
	rc = devm_snd_soc_register_card(&pdev->dev, &mioa701);
	if (!rc)
		dev_warn(&pdev->dev, "Be warned that incorrect mixers/muxes setup will "
			 "lead to overheating and possible destruction of your device."
			 " Do not use without a good knowledge of mio's board design!\n");
	return rc;
}