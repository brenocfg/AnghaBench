#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hda_fixup {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_6__ {TYPE_2__** pcm_rec; } ;
struct alc_spec {TYPE_3__ gen; } ;
struct TYPE_5__ {TYPE_1__* stream; } ;
struct TYPE_4__ {int /*<<< orphan*/  chmap; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_BUILD ; 
 int /*<<< orphan*/  asus_pcm_2_1_chmaps ; 

__attribute__((used)) static void alc_fixup_bass_chmap(struct hda_codec *codec,
				    const struct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_BUILD) {
		struct alc_spec *spec = codec->spec;
		spec->gen.pcm_rec[0]->stream[0].chmap = asus_pcm_2_1_chmaps;
	}
}