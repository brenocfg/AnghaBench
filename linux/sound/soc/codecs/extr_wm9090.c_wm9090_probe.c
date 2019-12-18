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
 int /*<<< orphan*/  WM9090_CLOCKING_1 ; 
 int WM9090_HPOUT1L_ZC ; 
 int WM9090_HPOUT1R_ZC ; 
 int WM9090_HPOUT1_VU ; 
 int WM9090_IN1A_ZC ; 
 int WM9090_IN1B_ZC ; 
 int /*<<< orphan*/  WM9090_IN1_LINE_INPUT_A_VOLUME ; 
 int /*<<< orphan*/  WM9090_IN1_LINE_INPUT_B_VOLUME ; 
 int WM9090_IN1_VU ; 
 int WM9090_IN2A_ZC ; 
 int WM9090_IN2B_ZC ; 
 int /*<<< orphan*/  WM9090_IN2_LINE_INPUT_A_VOLUME ; 
 int /*<<< orphan*/  WM9090_IN2_LINE_INPUT_B_VOLUME ; 
 int WM9090_IN2_VU ; 
 int /*<<< orphan*/  WM9090_LEFT_OUTPUT_VOLUME ; 
 int /*<<< orphan*/  WM9090_RIGHT_OUTPUT_VOLUME ; 
 int /*<<< orphan*/  WM9090_SPEAKER_VOLUME_LEFT ; 
 int WM9090_SPKOUTL_ZC ; 
 int WM9090_SPKOUT_VU ; 
 int WM9090_TOCLK_ENA ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wm9090_add_controls (struct snd_soc_component*) ; 

__attribute__((used)) static int wm9090_probe(struct snd_soc_component *component)
{
	/* Configure some defaults; they will be written out when we
	 * bring the bias up.
	 */
	snd_soc_component_update_bits(component, WM9090_IN1_LINE_INPUT_A_VOLUME,
			    WM9090_IN1_VU | WM9090_IN1A_ZC,
			    WM9090_IN1_VU | WM9090_IN1A_ZC);
	snd_soc_component_update_bits(component, WM9090_IN1_LINE_INPUT_B_VOLUME,
			    WM9090_IN1_VU | WM9090_IN1B_ZC,
			    WM9090_IN1_VU | WM9090_IN1B_ZC);
	snd_soc_component_update_bits(component, WM9090_IN2_LINE_INPUT_A_VOLUME,
			    WM9090_IN2_VU | WM9090_IN2A_ZC,
			    WM9090_IN2_VU | WM9090_IN2A_ZC);
	snd_soc_component_update_bits(component, WM9090_IN2_LINE_INPUT_B_VOLUME,
			    WM9090_IN2_VU | WM9090_IN2B_ZC,
			    WM9090_IN2_VU | WM9090_IN2B_ZC);
	snd_soc_component_update_bits(component, WM9090_SPEAKER_VOLUME_LEFT,
			    WM9090_SPKOUT_VU | WM9090_SPKOUTL_ZC,
			    WM9090_SPKOUT_VU | WM9090_SPKOUTL_ZC);
	snd_soc_component_update_bits(component, WM9090_LEFT_OUTPUT_VOLUME,
			    WM9090_HPOUT1_VU | WM9090_HPOUT1L_ZC,
			    WM9090_HPOUT1_VU | WM9090_HPOUT1L_ZC);
	snd_soc_component_update_bits(component, WM9090_RIGHT_OUTPUT_VOLUME,
			    WM9090_HPOUT1_VU | WM9090_HPOUT1R_ZC,
			    WM9090_HPOUT1_VU | WM9090_HPOUT1R_ZC);

	snd_soc_component_update_bits(component, WM9090_CLOCKING_1,
			    WM9090_TOCLK_ENA, WM9090_TOCLK_ENA);

	wm9090_add_controls(component);

	return 0;
}