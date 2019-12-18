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
 int DAC33_BCLKON ; 
 int DAC33_DACLPDNB ; 
 int DAC33_DACRPDNB ; 
 int DAC33_OSCPDNB ; 
 int /*<<< orphan*/  DAC33_PWR_CTRL ; 
 int /*<<< orphan*/  DAC33_SER_AUDIOIF_CTRL_B ; 
 int dac33_read_reg_cache (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac33_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void dac33_disable_digital(struct snd_soc_component *component)
{
	u8 reg;

	/* Stop the DAI clock */
	reg = dac33_read_reg_cache(component, DAC33_SER_AUDIOIF_CTRL_B);
	reg &= ~DAC33_BCLKON;
	dac33_write(component, DAC33_SER_AUDIOIF_CTRL_B, reg);

	/* Power down the Oscillator, and DACs */
	reg = dac33_read_reg_cache(component, DAC33_PWR_CTRL);
	reg &= ~(DAC33_OSCPDNB | DAC33_DACRPDNB | DAC33_DACLPDNB);
	dac33_write(component, DAC33_PWR_CTRL, reg);
}