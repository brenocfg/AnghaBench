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
struct hda_jack_tbl {int jack_dirty; int /*<<< orphan*/  tag; int /*<<< orphan*/  nid; } ;
struct TYPE_2__ {int /*<<< orphan*/  used; } ;
struct hda_codec {TYPE_1__ jacktbl; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 struct hda_jack_tbl* snd_array_new (TYPE_1__*) ; 
 struct hda_jack_tbl* snd_hda_jack_tbl_get (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hda_jack_tbl *
snd_hda_jack_tbl_new(struct hda_codec *codec, hda_nid_t nid)
{
	struct hda_jack_tbl *jack = snd_hda_jack_tbl_get(codec, nid);
	if (jack)
		return jack;
	jack = snd_array_new(&codec->jacktbl);
	if (!jack)
		return NULL;
	jack->nid = nid;
	jack->jack_dirty = 1;
	jack->tag = codec->jacktbl.used;
	return jack;
}