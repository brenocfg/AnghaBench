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
struct snd_soc_dapm_widget_list {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct dapm_kcontrol_data {struct snd_soc_dapm_widget_list* wlist; } ;

/* Variables and functions */
 struct dapm_kcontrol_data* snd_kcontrol_chip (struct snd_kcontrol const*) ; 

__attribute__((used)) static struct snd_soc_dapm_widget_list *dapm_kcontrol_get_wlist(
	const struct snd_kcontrol *kcontrol)
{
	struct dapm_kcontrol_data *data = snd_kcontrol_chip(kcontrol);

	return data->wlist;
}