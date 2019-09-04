#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hda_jack_tbl {int phantom_jack; int type; TYPE_1__* jack; } ;
struct hda_codec {int /*<<< orphan*/  card; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
struct TYPE_3__ {int /*<<< orphan*/  private_free; struct hda_jack_tbl* private_data; } ;

/* Variables and functions */
 int get_input_jack_type (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_free_jack_priv ; 
 int snd_hda_jack_detect (struct hda_codec*,int /*<<< orphan*/ ) ; 
 struct hda_jack_tbl* snd_hda_jack_tbl_new (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_jack_new (int /*<<< orphan*/ ,char const*,int,TYPE_1__**,int,int) ; 
 int /*<<< orphan*/  snd_jack_report (TYPE_1__*,int) ; 

int snd_hda_jack_add_kctl(struct hda_codec *codec, hda_nid_t nid,
			  const char *name, bool phantom_jack)
{
	struct hda_jack_tbl *jack;
	int err, state, type;

	jack = snd_hda_jack_tbl_new(codec, nid);
	if (!jack)
		return 0;
	if (jack->jack)
		return 0; /* already created */

	type = get_input_jack_type(codec, nid);
	err = snd_jack_new(codec->card, name, type,
			   &jack->jack, true, phantom_jack);
	if (err < 0)
		return err;

	jack->phantom_jack = !!phantom_jack;
	jack->type = type;
	jack->jack->private_data = jack;
	jack->jack->private_free = hda_free_jack_priv;
	state = snd_hda_jack_detect(codec, nid);
	snd_jack_report(jack->jack, state ? jack->type : 0);

	return 0;
}