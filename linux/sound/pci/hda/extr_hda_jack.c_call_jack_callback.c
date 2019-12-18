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
struct hda_jack_tbl {struct hda_jack_callback* callback; scalar_t__ gated_jack; } ;
struct hda_jack_callback {unsigned int unsol_res; int /*<<< orphan*/  (* func ) (struct hda_codec*,struct hda_jack_callback*) ;struct hda_jack_tbl* jack; struct hda_jack_callback* next; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 struct hda_jack_tbl* snd_hda_jack_tbl_get (struct hda_codec*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*,struct hda_jack_callback*) ; 
 int /*<<< orphan*/  stub2 (struct hda_codec*,struct hda_jack_callback*) ; 

__attribute__((used)) static void call_jack_callback(struct hda_codec *codec, unsigned int res,
			       struct hda_jack_tbl *jack)
{
	struct hda_jack_callback *cb;

	for (cb = jack->callback; cb; cb = cb->next) {
		cb->jack = jack;
		cb->unsol_res = res;
		cb->func(codec, cb);
	}
	if (jack->gated_jack) {
		struct hda_jack_tbl *gated =
			snd_hda_jack_tbl_get(codec, jack->gated_jack);
		if (gated) {
			for (cb = gated->callback; cb; cb = cb->next) {
				cb->jack = gated;
				cb->unsol_res = res;
				cb->func(codec, cb);
			}
		}
	}
}