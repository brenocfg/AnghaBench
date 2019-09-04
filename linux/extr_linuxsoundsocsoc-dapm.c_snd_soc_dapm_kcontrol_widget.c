#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dapm_widget {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_2__ {struct snd_soc_dapm_widget** widgets; } ;

/* Variables and functions */
 TYPE_1__* dapm_kcontrol_get_wlist (struct snd_kcontrol*) ; 

struct snd_soc_dapm_widget *snd_soc_dapm_kcontrol_widget(
				struct snd_kcontrol *kcontrol)
{
	return dapm_kcontrol_get_wlist(kcontrol)->widgets[0];
}