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
struct TYPE_2__ {int /*<<< orphan*/  hp_outs; } ;
struct hda_gen_spec {int /*<<< orphan*/  hp_paths; TYPE_1__ autocfg; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int create_extra_outs (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int create_hp_out_ctls(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	return create_extra_outs(codec, spec->autocfg.hp_outs,
				 spec->hp_paths,
				 "Headphone");
}