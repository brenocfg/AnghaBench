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
struct hda_jack_tbl {int block_report; } ;
struct hda_jack_callback {int /*<<< orphan*/  nid; } ;
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {int /*<<< orphan*/  unsol_hp_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hda_jack_tbl* snd_hda_jack_tbl_get (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hp_callback(struct hda_codec *codec, struct hda_jack_callback *cb)
{
	struct ca0132_spec *spec = codec->spec;
	struct hda_jack_tbl *tbl;

	/* Delay enabling the HP amp, to let the mic-detection
	 * state machine run.
	 */
	cancel_delayed_work(&spec->unsol_hp_work);
	schedule_delayed_work(&spec->unsol_hp_work, msecs_to_jiffies(500));
	tbl = snd_hda_jack_tbl_get(codec, cb->nid);
	if (tbl)
		tbl->block_report = 1;
}