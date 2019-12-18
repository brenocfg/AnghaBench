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
struct snd_kcontrol {int /*<<< orphan*/  private_free; struct snd_jack_kctl* private_data; } ;
struct snd_jack_kctl {unsigned int mask_bits; struct snd_kcontrol* kctl; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_jack_kctl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_ctl_free_one (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_jack_kctl_private_free ; 
 struct snd_kcontrol* snd_kctl_jack_new (char const*,struct snd_card*) ; 

__attribute__((used)) static struct snd_jack_kctl * snd_jack_kctl_new(struct snd_card *card, const char *name, unsigned int mask)
{
	struct snd_kcontrol *kctl;
	struct snd_jack_kctl *jack_kctl;
	int err;

	kctl = snd_kctl_jack_new(name, card);
	if (!kctl)
		return NULL;

	err = snd_ctl_add(card, kctl);
	if (err < 0)
		return NULL;

	jack_kctl = kzalloc(sizeof(*jack_kctl), GFP_KERNEL);

	if (!jack_kctl)
		goto error;

	jack_kctl->kctl = kctl;
	jack_kctl->mask_bits = mask;

	kctl->private_data = jack_kctl;
	kctl->private_free = snd_jack_kctl_private_free;

	return jack_kctl;
error:
	snd_ctl_free_one(kctl);
	return NULL;
}