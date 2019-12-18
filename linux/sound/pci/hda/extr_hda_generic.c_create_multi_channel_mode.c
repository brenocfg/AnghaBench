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
struct hda_gen_spec {scalar_t__ multi_ios; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  channel_mode_enum ; 
 int /*<<< orphan*/  snd_hda_gen_add_kctl (struct hda_gen_spec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_multi_channel_mode(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;

	if (spec->multi_ios > 0) {
		if (!snd_hda_gen_add_kctl(spec, NULL, &channel_mode_enum))
			return -ENOMEM;
	}
	return 0;
}