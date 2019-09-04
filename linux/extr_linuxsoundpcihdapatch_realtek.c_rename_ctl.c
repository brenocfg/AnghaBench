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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 struct snd_kcontrol* snd_hda_find_mixer_ctl (struct hda_codec*,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void rename_ctl(struct hda_codec *codec, const char *oldname,
		       const char *newname)
{
	struct snd_kcontrol *kctl;

	kctl = snd_hda_find_mixer_ctl(codec, oldname);
	if (kctl)
		strcpy(kctl->id.name, newname);
}