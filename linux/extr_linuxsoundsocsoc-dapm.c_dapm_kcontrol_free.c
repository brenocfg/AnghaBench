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
struct snd_kcontrol {int dummy; } ;
struct dapm_kcontrol_data {struct dapm_kcontrol_data* wlist; int /*<<< orphan*/  paths; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct dapm_kcontrol_data*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct dapm_kcontrol_data* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static void dapm_kcontrol_free(struct snd_kcontrol *kctl)
{
	struct dapm_kcontrol_data *data = snd_kcontrol_chip(kctl);

	list_del(&data->paths);
	kfree(data->wlist);
	kfree(data);
}