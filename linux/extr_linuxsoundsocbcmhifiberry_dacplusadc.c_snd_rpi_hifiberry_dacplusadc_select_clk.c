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
#define  HIFIBERRY_DACPRO_CLK44EN 130 
#define  HIFIBERRY_DACPRO_CLK48EN 129 
#define  HIFIBERRY_DACPRO_NOCLOCK 128 
 int /*<<< orphan*/  PCM512x_GPIO_CONTROL_1 ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void snd_rpi_hifiberry_dacplusadc_select_clk(struct snd_soc_component *component,
	int clk_id)
{
	switch (clk_id) {
	case HIFIBERRY_DACPRO_NOCLOCK:
		snd_soc_component_update_bits(component, PCM512x_GPIO_CONTROL_1, 0x24, 0x00);
		break;
	case HIFIBERRY_DACPRO_CLK44EN:
		snd_soc_component_update_bits(component, PCM512x_GPIO_CONTROL_1, 0x24, 0x20);
		break;
	case HIFIBERRY_DACPRO_CLK48EN:
		snd_soc_component_update_bits(component, PCM512x_GPIO_CONTROL_1, 0x24, 0x04);
		break;
	}
}