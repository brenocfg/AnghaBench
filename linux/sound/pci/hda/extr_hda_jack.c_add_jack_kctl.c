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
struct hda_codec {int dummy; } ;
struct auto_pin_cfg {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_JACK_PORT_COMPLEX ; 
 unsigned int AC_JACK_PORT_NONE ; 
 int SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 unsigned int get_defcfg_connect (unsigned int) ; 
 int /*<<< orphan*/  is_jack_detectable (struct hda_codec*,int /*<<< orphan*/ ) ; 
 unsigned int snd_hda_codec_get_pincfg (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_get_pin_label (struct hda_codec*,int /*<<< orphan*/ ,struct auto_pin_cfg const*,char*,int,int /*<<< orphan*/ *) ; 
 int snd_hda_jack_add_kctl (struct hda_codec*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int snd_hda_jack_detect_enable (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 

__attribute__((used)) static int add_jack_kctl(struct hda_codec *codec, hda_nid_t nid,
			 const struct auto_pin_cfg *cfg,
			 const char *base_name)
{
	unsigned int def_conf, conn;
	char name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	int err;
	bool phantom_jack;

	if (!nid)
		return 0;
	def_conf = snd_hda_codec_get_pincfg(codec, nid);
	conn = get_defcfg_connect(def_conf);
	if (conn == AC_JACK_PORT_NONE)
		return 0;
	phantom_jack = (conn != AC_JACK_PORT_COMPLEX) ||
		       !is_jack_detectable(codec, nid);

	if (base_name)
		strlcpy(name, base_name, sizeof(name));
	else
		snd_hda_get_pin_label(codec, nid, cfg, name, sizeof(name), NULL);
	if (phantom_jack)
		/* Example final name: "Internal Mic Phantom Jack" */
		strncat(name, " Phantom", sizeof(name) - strlen(name) - 1);
	err = snd_hda_jack_add_kctl(codec, nid, name, phantom_jack, 0, NULL);
	if (err < 0)
		return err;

	if (!phantom_jack)
		return snd_hda_jack_detect_enable(codec, nid);
	return 0;
}