#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct hda_amp_list* amplist; } ;
struct TYPE_4__ {TYPE_1__ loopback; } ;
struct via_spec {TYPE_2__ gen; } ;
struct hda_codec {struct via_spec* spec; } ;
struct hda_amp_list {int /*<<< orphan*/  idx; int /*<<< orphan*/  dir; scalar_t__ nid; } ;

/* Variables and functions */
 int HDA_AMP_MUTE ; 
 int snd_hda_codec_amp_read (struct hda_codec*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_aa_path_mute(struct hda_codec *codec)
{
	struct via_spec *spec = codec->spec;
	const struct hda_amp_list *p;
	int ch, v;

	p = spec->gen.loopback.amplist;
	if (!p)
		return true;
	for (; p->nid; p++) {
		for (ch = 0; ch < 2; ch++) {
			v = snd_hda_codec_amp_read(codec, p->nid, ch, p->dir,
						   p->idx);
			if (!(v & HDA_AMP_MUTE) && v > 0)
				return false;
		}
	}
	return true;
}