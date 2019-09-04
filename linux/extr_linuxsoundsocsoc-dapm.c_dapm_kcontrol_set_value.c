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
struct snd_kcontrol {int dummy; } ;
struct dapm_kcontrol_data {unsigned int value; TYPE_1__* widget; } ;
struct TYPE_2__ {unsigned int on_val; } ;

/* Variables and functions */
 struct dapm_kcontrol_data* snd_kcontrol_chip (struct snd_kcontrol const*) ; 

__attribute__((used)) static bool dapm_kcontrol_set_value(const struct snd_kcontrol *kcontrol,
	unsigned int value)
{
	struct dapm_kcontrol_data *data = snd_kcontrol_chip(kcontrol);

	if (data->value == value)
		return false;

	if (data->widget)
		data->widget->on_val = value;

	data->value = value;

	return true;
}