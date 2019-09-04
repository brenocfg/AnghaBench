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
struct TYPE_2__ {int line_outs; } ;
struct hda_gen_spec {int /*<<< orphan*/ * out_paths; TYPE_1__ autocfg; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_output_and_unmute (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_multi_out(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	int i;

	for (i = 0; i < spec->autocfg.line_outs; i++)
		set_output_and_unmute(codec, spec->out_paths[i]);
}