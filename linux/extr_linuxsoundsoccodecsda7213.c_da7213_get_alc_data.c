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
 int DA7213_ALC_AVG_ITERATIONS ; 
 int /*<<< orphan*/  DA7213_ALC_CIC_OP_LVL_CTRL ; 
 int /*<<< orphan*/  DA7213_ALC_CIC_OP_LVL_DATA ; 
 int DA7213_ALC_DATA_MIDDLE ; 
 int DA7213_ALC_DATA_TOP ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int da7213_get_alc_data(struct snd_soc_component *component, u8 reg_val)
{
	int mid_data, top_data;
	int sum = 0;
	u8 iteration;

	for (iteration = 0; iteration < DA7213_ALC_AVG_ITERATIONS;
	     iteration++) {
		/* Select the left or right channel and capture data */
		snd_soc_component_write(component, DA7213_ALC_CIC_OP_LVL_CTRL, reg_val);

		/* Select middle 8 bits for read back from data register */
		snd_soc_component_write(component, DA7213_ALC_CIC_OP_LVL_CTRL,
			      reg_val | DA7213_ALC_DATA_MIDDLE);
		mid_data = snd_soc_component_read32(component, DA7213_ALC_CIC_OP_LVL_DATA);

		/* Select top 8 bits for read back from data register */
		snd_soc_component_write(component, DA7213_ALC_CIC_OP_LVL_CTRL,
			      reg_val | DA7213_ALC_DATA_TOP);
		top_data = snd_soc_component_read32(component, DA7213_ALC_CIC_OP_LVL_DATA);

		sum += ((mid_data << 8) | (top_data << 16));
	}

	return sum / DA7213_ALC_AVG_ITERATIONS;
}