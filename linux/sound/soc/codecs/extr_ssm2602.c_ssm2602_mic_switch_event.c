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
struct snd_soc_dapm_widget {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int ssm2602_mic_switch_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	/*
	 * According to the ssm2603 data sheet (control register sequencing),
	 * the digital core should be activated only after all necessary bits
	 * in the power register are enabled, and a delay determined by the
	 * decoupling capacitor on the VMID pin has passed. If the digital core
	 * is activated too early, or even before the ADC is powered up, audible
	 * artifacts appear at the beginning and end of the recorded signal.
	 *
	 * In practice, audible artifacts disappear well over 500 ms.
	 */
	msleep(500);

	return 0;
}