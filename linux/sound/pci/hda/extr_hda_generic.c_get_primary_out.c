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
struct auto_pin_cfg {int line_outs; } ;
struct hda_gen_spec {int multi_ios; TYPE_1__* multi_io; int /*<<< orphan*/ * private_dac_nids; struct auto_pin_cfg autocfg; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
struct TYPE_2__ {int /*<<< orphan*/  dac; } ;

/* Variables and functions */

__attribute__((used)) static hda_nid_t get_primary_out(struct hda_codec *codec, int idx)
{
	struct hda_gen_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->autocfg;

	if (cfg->line_outs > idx)
		return spec->private_dac_nids[idx];
	idx -= cfg->line_outs;
	if (spec->multi_ios > idx)
		return spec->multi_io[idx].dac;
	return 0;
}