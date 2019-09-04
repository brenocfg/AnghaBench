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
struct TYPE_2__ {int /*<<< orphan*/  afg; } ;
struct hda_codec {TYPE_1__ core; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_WCAP_DIGITAL ; 
#define  AC_WID_AUD_OUT 129 
#define  AC_WID_PIN 128 
 int EINVAL ; 
 int /*<<< orphan*/  codec_warn (struct hda_codec*,char*) ; 
 unsigned int get_wcaps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 unsigned int get_wcaps_type (unsigned int) ; 
 int /*<<< orphan*/  hdmi_add_cvt (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_add_pin (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_get_sub_nodes (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdmi_parse_codec(struct hda_codec *codec)
{
	hda_nid_t nid;
	int i, nodes;

	nodes = snd_hda_get_sub_nodes(codec, codec->core.afg, &nid);
	if (!nid || nodes < 0) {
		codec_warn(codec, "HDMI: failed to get afg sub nodes\n");
		return -EINVAL;
	}

	for (i = 0; i < nodes; i++, nid++) {
		unsigned int caps;
		unsigned int type;

		caps = get_wcaps(codec, nid);
		type = get_wcaps_type(caps);

		if (!(caps & AC_WCAP_DIGITAL))
			continue;

		switch (type) {
		case AC_WID_AUD_OUT:
			hdmi_add_cvt(codec, nid);
			break;
		case AC_WID_PIN:
			hdmi_add_pin(codec, nid);
			break;
		}
	}

	return 0;
}