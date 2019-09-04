#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ platform_data; } ;
struct platform_device {TYPE_3__ dev; } ;
struct palm27x_asoc_info {int /*<<< orphan*/  jack_gpio; } ;
struct TYPE_7__ {int /*<<< orphan*/  gpio; } ;
struct TYPE_6__ {TYPE_3__* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int devm_snd_soc_register_card (TYPE_3__*,TYPE_1__*) ; 
 TYPE_2__* hs_jack_gpios ; 
 scalar_t__ machine_is_palmld () ; 
 scalar_t__ machine_is_palmt5 () ; 
 scalar_t__ machine_is_palmte2 () ; 
 scalar_t__ machine_is_palmtx () ; 
 TYPE_1__ palm27x_asoc ; 

__attribute__((used)) static int palm27x_asoc_probe(struct platform_device *pdev)
{
	int ret;

	if (!(machine_is_palmtx() || machine_is_palmt5() ||
		machine_is_palmld() || machine_is_palmte2()))
		return -ENODEV;

	if (!pdev->dev.platform_data) {
		dev_err(&pdev->dev, "please supply platform_data\n");
		return -ENODEV;
	}

	hs_jack_gpios[0].gpio = ((struct palm27x_asoc_info *)
			(pdev->dev.platform_data))->jack_gpio;

	palm27x_asoc.dev = &pdev->dev;

	ret = devm_snd_soc_register_card(&pdev->dev, &palm27x_asoc);
	if (ret)
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);
	return ret;
}