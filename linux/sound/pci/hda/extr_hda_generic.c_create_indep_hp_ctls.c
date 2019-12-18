#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* hp_out_nid; scalar_t__* dac_nids; } ;
struct TYPE_4__ {scalar_t__ line_out_type; } ;
struct hda_gen_spec {int indep_hp_enabled; scalar_t__ alt_dac_nid; scalar_t__ indep_hp; TYPE_1__ multiout; TYPE_2__ autocfg; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 scalar_t__ AUTO_PIN_HP_OUT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  indep_hp_ctl ; 
 int /*<<< orphan*/  snd_hda_gen_add_kctl (struct hda_gen_spec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_indep_hp_ctls(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	hda_nid_t dac;

	if (!spec->indep_hp)
		return 0;
	if (spec->autocfg.line_out_type == AUTO_PIN_HP_OUT)
		dac = spec->multiout.dac_nids[0];
	else
		dac = spec->multiout.hp_out_nid[0];
	if (!dac) {
		spec->indep_hp = 0;
		return 0;
	}

	spec->indep_hp_enabled = false;
	spec->alt_dac_nid = dac;
	if (!snd_hda_gen_add_kctl(spec, NULL, &indep_hp_ctl))
		return -ENOMEM;
	return 0;
}