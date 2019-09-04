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
struct hda_gen_spec {int dummy; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  automute_mode_enum ; 
 int /*<<< orphan*/  snd_hda_gen_add_kctl (struct hda_gen_spec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_automute_mode_enum(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;

	if (!snd_hda_gen_add_kctl(spec, NULL, &automute_mode_enum))
		return -ENOMEM;
	return 0;
}