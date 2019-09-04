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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5651_IRQ_CTRL2 ; 
 int /*<<< orphan*/  RT5651_MB1_OC_CLR ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt5651_clear_micbias1_ovcd(struct snd_soc_component *component)
{
	snd_soc_component_update_bits(component, RT5651_IRQ_CTRL2,
		RT5651_MB1_OC_CLR, 0);
}