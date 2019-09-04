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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int devm_snd_soc_register_card (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_free_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpio_request_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx4700_audio_gpios ; 
 int /*<<< orphan*/  machine_is_h4700 () ; 
 TYPE_1__ snd_soc_card_hx4700 ; 

__attribute__((used)) static int hx4700_audio_probe(struct platform_device *pdev)
{
	int ret;

	if (!machine_is_h4700())
		return -ENODEV;

	ret = gpio_request_array(hx4700_audio_gpios,
				ARRAY_SIZE(hx4700_audio_gpios));
	if (ret)
		return ret;

	snd_soc_card_hx4700.dev = &pdev->dev;
	ret = devm_snd_soc_register_card(&pdev->dev, &snd_soc_card_hx4700);
	if (ret)
		gpio_free_array(hx4700_audio_gpios,
				ARRAY_SIZE(hx4700_audio_gpios));

	return ret;
}