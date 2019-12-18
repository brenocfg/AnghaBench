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
struct TYPE_3__ {int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 int alsa_card_pcsp_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ pcsp_chip ; 
 int pcspkr_input_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcspkr_input_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_1__*) ; 

__attribute__((used)) static int pcsp_probe(struct platform_device *dev)
{
	int err;

	err = pcspkr_input_init(&pcsp_chip.input_dev, &dev->dev);
	if (err < 0)
		return err;

	err = alsa_card_pcsp_init(&dev->dev);
	if (err < 0) {
		pcspkr_input_remove(pcsp_chip.input_dev);
		return err;
	}

	platform_set_drvdata(dev, &pcsp_chip);
	return 0;
}