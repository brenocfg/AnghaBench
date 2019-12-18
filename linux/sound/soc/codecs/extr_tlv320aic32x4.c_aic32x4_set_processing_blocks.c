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
typedef  int u8 ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC32X4_ADCSPB ; 
 int /*<<< orphan*/  AIC32X4_DACSPB ; 
 int EINVAL ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aic32x4_set_processing_blocks(struct snd_soc_component *component,
						u8 r_block, u8 p_block)
{
	if (r_block > 18 || p_block > 25)
		return -EINVAL;

	snd_soc_component_write(component, AIC32X4_ADCSPB, r_block);
	snd_soc_component_write(component, AIC32X4_DACSPB, p_block);

	return 0;
}