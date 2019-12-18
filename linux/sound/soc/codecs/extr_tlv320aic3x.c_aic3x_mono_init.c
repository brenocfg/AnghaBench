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
 int /*<<< orphan*/  DACL1_2_MONOLOPM_VOL ; 
 int /*<<< orphan*/  DACR1_2_MONOLOPM_VOL ; 
 int DEFAULT_VOL ; 
 int /*<<< orphan*/  LINE2L_2_MONOLOPM_VOL ; 
 int /*<<< orphan*/  LINE2R_2_MONOLOPM_VOL ; 
 int /*<<< orphan*/  MONOLOPM_CTRL ; 
 int /*<<< orphan*/  PGAL_2_MONOLOPM_VOL ; 
 int /*<<< orphan*/  PGAR_2_MONOLOPM_VOL ; 
 int ROUTE_ON ; 
 int /*<<< orphan*/  UNMUTE ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aic3x_mono_init(struct snd_soc_component *component)
{
	/* DAC to Mono Line Out default volume and route to Output mixer */
	snd_soc_component_write(component, DACL1_2_MONOLOPM_VOL, DEFAULT_VOL | ROUTE_ON);
	snd_soc_component_write(component, DACR1_2_MONOLOPM_VOL, DEFAULT_VOL | ROUTE_ON);

	/* unmute all outputs */
	snd_soc_component_update_bits(component, MONOLOPM_CTRL, UNMUTE, UNMUTE);

	/* PGA to Mono Line Out default volume, disconnect from Output Mixer */
	snd_soc_component_write(component, PGAL_2_MONOLOPM_VOL, DEFAULT_VOL);
	snd_soc_component_write(component, PGAR_2_MONOLOPM_VOL, DEFAULT_VOL);

	/* Line2 to Mono Out default volume, disconnect from Output Mixer */
	snd_soc_component_write(component, LINE2L_2_MONOLOPM_VOL, DEFAULT_VOL);
	snd_soc_component_write(component, LINE2R_2_MONOLOPM_VOL, DEFAULT_VOL);
}