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
struct TYPE_2__ {int /*<<< orphan*/ * c; } ;
struct snd_kcontrol_new {int /*<<< orphan*/  private_value; int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  info; TYPE_1__ tlv; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 struct snd_kcontrol_new HDA_CODEC_VOLUME_MONO (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HDA_COMPOSE_AMP_VAL (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int HDA_INPUT ; 
 int HDA_OUTPUT ; 
 int SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
#define  XBASS_XOVER 128 
 int /*<<< orphan*/  ca0132_alt_effect_slider_info ; 
 int /*<<< orphan*/  ca0132_alt_effect_slider_put ; 
 int /*<<< orphan*/  ca0132_alt_slider_ctl_get ; 
 int /*<<< orphan*/  ca0132_alt_xbass_xover_slider_ctl_get ; 
 int /*<<< orphan*/  ca0132_alt_xbass_xover_slider_info ; 
 int /*<<< orphan*/  ca0132_alt_xbass_xover_slider_put ; 
 char** dirstr ; 
 int /*<<< orphan*/  snd_ctl_new1 (struct snd_kcontrol_new*,struct hda_codec*) ; 
 int snd_hda_ctl_add (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*) ; 

__attribute__((used)) static int ca0132_alt_add_effect_slider(struct hda_codec *codec, hda_nid_t nid,
					const char *pfx, int dir)
{
	char namestr[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	int type = dir ? HDA_INPUT : HDA_OUTPUT;
	struct snd_kcontrol_new knew =
		HDA_CODEC_VOLUME_MONO(namestr, nid, 1, 0, type);

	sprintf(namestr, "FX: %s %s Volume", pfx, dirstr[dir]);

	knew.tlv.c = NULL;

	switch (nid) {
	case XBASS_XOVER:
		knew.info = ca0132_alt_xbass_xover_slider_info;
		knew.get = ca0132_alt_xbass_xover_slider_ctl_get;
		knew.put = ca0132_alt_xbass_xover_slider_put;
		break;
	default:
		knew.info = ca0132_alt_effect_slider_info;
		knew.get = ca0132_alt_slider_ctl_get;
		knew.put = ca0132_alt_effect_slider_put;
		knew.private_value =
			HDA_COMPOSE_AMP_VAL(nid, 1, 0, type);
		break;
	}

	return snd_hda_ctl_add(codec, nid, snd_ctl_new1(&knew, codec));
}