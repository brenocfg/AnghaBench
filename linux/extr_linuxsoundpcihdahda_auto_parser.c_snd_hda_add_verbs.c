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
struct hda_verb {int dummy; } ;
struct hda_codec {int /*<<< orphan*/  verbs; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct hda_verb** snd_array_new (int /*<<< orphan*/ *) ; 

int snd_hda_add_verbs(struct hda_codec *codec,
		      const struct hda_verb *list)
{
	const struct hda_verb **v;
	v = snd_array_new(&codec->verbs);
	if (!v)
		return -ENOMEM;
	*v = list;
	return 0;
}