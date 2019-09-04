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
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {int done_hp_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  alc294_hp_init (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_default_init (struct hda_codec*) ; 

__attribute__((used)) static void alc294_init(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;

	if (!spec->done_hp_init) {
		alc294_hp_init(codec);
		spec->done_hp_init = true;
	}
	alc_default_init(codec);
}