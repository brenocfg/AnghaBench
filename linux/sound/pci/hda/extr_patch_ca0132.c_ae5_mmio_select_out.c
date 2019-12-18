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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {size_t cur_out_type; } ;
struct TYPE_2__ {int /*<<< orphan*/ * vals; int /*<<< orphan*/ * target; int /*<<< orphan*/ * group; } ;

/* Variables and functions */
 unsigned int AE5_CA0113_OUT_SET_COMMANDS ; 
 TYPE_1__* ae5_ca0113_output_presets ; 
 int /*<<< orphan*/  ca0113_mmio_command_set (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ae5_mmio_select_out(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned int i;

	for (i = 0; i < AE5_CA0113_OUT_SET_COMMANDS; i++)
		ca0113_mmio_command_set(codec,
			ae5_ca0113_output_presets[spec->cur_out_type].group[i],
			ae5_ca0113_output_presets[spec->cur_out_type].target[i],
			ae5_ca0113_output_presets[spec->cur_out_type].vals[i]);
}