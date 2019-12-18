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
struct hda_codec {struct ad198x_spec* spec; } ;
struct TYPE_3__ {int /*<<< orphan*/  dig_out_nid; } ;
struct TYPE_4__ {TYPE_1__ multiout; } ;
struct ad198x_spec {TYPE_2__ gen; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ad1983_auto_smux_mixer ; 
 int /*<<< orphan*/  snd_hda_gen_add_kctl (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int snd_hda_get_num_conns (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad1983_add_spdif_mux_ctl(struct hda_codec *codec)
{
	struct ad198x_spec *spec = codec->spec;
	hda_nid_t dig_out = spec->gen.multiout.dig_out_nid;
	int num_conns;

	if (!dig_out)
		return 0;
	num_conns = snd_hda_get_num_conns(codec, dig_out);
	if (num_conns != 2 && num_conns != 3)
		return 0;
	if (!snd_hda_gen_add_kctl(&spec->gen, NULL, &ad1983_auto_smux_mixer))
		return -ENOMEM;
	return 0;
}