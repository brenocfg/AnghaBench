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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct snd_kcontrol {TYPE_1__ id; } ;
struct snd_card {int /*<<< orphan*/  shortname; } ;

/* Variables and functions */
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void check_no_speaker_on_headset(struct snd_kcontrol *kctl,
					struct snd_card *card)
{
	const char *names_to_check[] = {
		"Headset", "headset", "Headphone", "headphone", NULL};
	const char **s;
	bool found = false;

	if (strcmp("Speaker", kctl->id.name))
		return;

	for (s = names_to_check; *s; s++)
		if (strstr(card->shortname, *s)) {
			found = true;
			break;
		}

	if (!found)
		return;

	strlcpy(kctl->id.name, "Headphone", sizeof(kctl->id.name));
}