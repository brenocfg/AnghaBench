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
struct hda_codec {int /*<<< orphan*/ * spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_FIXUP_ACT_FREE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_apply_fixup (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_gen_spec_free (int /*<<< orphan*/ *) ; 

void snd_hda_gen_free(struct hda_codec *codec)
{
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_FREE);
	snd_hda_gen_spec_free(codec->spec);
	kfree(codec->spec);
	codec->spec = NULL;
}