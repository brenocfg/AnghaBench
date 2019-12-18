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
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7219_DAI_BCLKS_PER_WCLK_128 ; 
 int /*<<< orphan*/  DA7219_DAI_BCLKS_PER_WCLK_256 ; 
 int /*<<< orphan*/  DA7219_DAI_BCLKS_PER_WCLK_32 ; 
 int /*<<< orphan*/  DA7219_DAI_BCLKS_PER_WCLK_64 ; 
 int /*<<< orphan*/  DA7219_DAI_BCLKS_PER_WCLK_MASK ; 
 int /*<<< orphan*/  DA7219_DAI_CLK_MODE ; 
 int EINVAL ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da7219_set_bclks_per_wclk(struct snd_soc_component *component,
				     unsigned long factor)
{
	u8 bclks_per_wclk;

	switch (factor) {
	case 32:
		bclks_per_wclk = DA7219_DAI_BCLKS_PER_WCLK_32;
		break;
	case 64:
		bclks_per_wclk = DA7219_DAI_BCLKS_PER_WCLK_64;
		break;
	case 128:
		bclks_per_wclk = DA7219_DAI_BCLKS_PER_WCLK_128;
		break;
	case 256:
		bclks_per_wclk = DA7219_DAI_BCLKS_PER_WCLK_256;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, DA7219_DAI_CLK_MODE,
				      DA7219_DAI_BCLKS_PER_WCLK_MASK,
				      bclks_per_wclk);

	return 0;
}