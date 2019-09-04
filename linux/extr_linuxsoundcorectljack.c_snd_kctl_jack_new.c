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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  index; } ;
struct snd_kcontrol {scalar_t__ private_value; TYPE_1__ id; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_available_index (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jack_detect_kctl ; 
 int /*<<< orphan*/  jack_kctl_name_gen (int /*<<< orphan*/ ,char const*,int) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct snd_kcontrol *
snd_kctl_jack_new(const char *name, struct snd_card *card)
{
	struct snd_kcontrol *kctl;

	kctl = snd_ctl_new1(&jack_detect_kctl, NULL);
	if (!kctl)
		return NULL;

	jack_kctl_name_gen(kctl->id.name, name, sizeof(kctl->id.name));
	kctl->id.index = get_available_index(card, kctl->id.name);
	kctl->private_value = 0;
	return kctl;
}