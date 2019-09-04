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
 int /*<<< orphan*/  RT5651_IRQ_CTRL2 ; 
 int RT5651_MB1_OC_CLR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rt5651_micbias1_ovcd(struct snd_soc_component *component)
{
	int val;

	val = snd_soc_component_read32(component, RT5651_IRQ_CTRL2);
	dev_dbg(component->dev, "irq ctrl2 %#04x\n", val);

	return (val & RT5651_MB1_OC_CLR);
}