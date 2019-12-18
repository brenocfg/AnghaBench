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
 int max98095_line_pga (struct snd_soc_dapm_widget*,int,int) ; 

__attribute__((used)) static int max98095_pga_in1_event(struct snd_soc_dapm_widget *w,
				   struct snd_kcontrol *k, int event)
{
	return max98095_line_pga(w, event, 1);
}