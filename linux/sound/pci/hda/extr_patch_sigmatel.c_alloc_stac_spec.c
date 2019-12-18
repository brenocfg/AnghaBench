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
struct TYPE_2__ {int dac_min_mute; } ;
struct sigmatel_spec {TYPE_1__ gen; } ;
struct hda_codec {int no_trigger_sense; int /*<<< orphan*/  patch_ops; struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sigmatel_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_gen_spec_init (TYPE_1__*) ; 
 int /*<<< orphan*/  stac_patch_ops ; 

__attribute__((used)) static int alloc_stac_spec(struct hda_codec *codec)
{
	struct sigmatel_spec *spec;

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	snd_hda_gen_spec_init(&spec->gen);
	codec->spec = spec;
	codec->no_trigger_sense = 1; /* seems common with STAC/IDT codecs */
	spec->gen.dac_min_mute = true;
	codec->patch_ops = stac_patch_ops;
	return 0;
}