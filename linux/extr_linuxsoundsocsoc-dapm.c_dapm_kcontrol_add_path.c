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
struct snd_soc_dapm_path {int /*<<< orphan*/  list_kcontrol; } ;
struct snd_kcontrol {int dummy; } ;
struct dapm_kcontrol_data {int /*<<< orphan*/  paths; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dapm_kcontrol_data* snd_kcontrol_chip (struct snd_kcontrol const*) ; 

__attribute__((used)) static void dapm_kcontrol_add_path(const struct snd_kcontrol *kcontrol,
	struct snd_soc_dapm_path *path)
{
	struct dapm_kcontrol_data *data = snd_kcontrol_chip(kcontrol);

	list_add_tail(&path->list_kcontrol, &data->paths);
}