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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8711_LOUT1V ; 
 int /*<<< orphan*/  WM8711_ROUT1V ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int wm8711_reset (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8711_probe(struct snd_soc_component *component)
{
	int ret;

	ret = wm8711_reset(component);
	if (ret < 0) {
		dev_err(component->dev, "Failed to issue reset\n");
		return ret;
	}

	/* Latch the update bits */
	snd_soc_component_update_bits(component, WM8711_LOUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8711_ROUT1V, 0x0100, 0x0100);

	return ret;

}