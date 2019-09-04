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
struct TYPE_2__ {scalar_t__ line_out_type; int /*<<< orphan*/  speaker_outs; int /*<<< orphan*/  hp_outs; } ;
struct hda_gen_spec {int /*<<< orphan*/  speaker_paths; TYPE_1__ autocfg; int /*<<< orphan*/  hp_paths; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 scalar_t__ AUTO_PIN_HP_OUT ; 
 scalar_t__ AUTO_PIN_SPEAKER_OUT ; 
 int /*<<< orphan*/  __init_extra_out (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_extra_out(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;

	if (spec->autocfg.line_out_type != AUTO_PIN_HP_OUT)
		__init_extra_out(codec, spec->autocfg.hp_outs, spec->hp_paths);
	if (spec->autocfg.line_out_type != AUTO_PIN_SPEAKER_OUT)
		__init_extra_out(codec, spec->autocfg.speaker_outs,
				 spec->speaker_paths);
}