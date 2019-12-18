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
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {int codec_variant; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
#define  ALC269_TYPE_ALC215 147 
#define  ALC269_TYPE_ALC225 146 
#define  ALC269_TYPE_ALC255 145 
#define  ALC269_TYPE_ALC256 144 
#define  ALC269_TYPE_ALC257 143 
#define  ALC269_TYPE_ALC269VA 142 
#define  ALC269_TYPE_ALC269VB 141 
#define  ALC269_TYPE_ALC269VC 140 
#define  ALC269_TYPE_ALC269VD 139 
#define  ALC269_TYPE_ALC280 138 
#define  ALC269_TYPE_ALC282 137 
#define  ALC269_TYPE_ALC283 136 
#define  ALC269_TYPE_ALC284 135 
#define  ALC269_TYPE_ALC286 134 
#define  ALC269_TYPE_ALC293 133 
#define  ALC269_TYPE_ALC294 132 
#define  ALC269_TYPE_ALC298 131 
#define  ALC269_TYPE_ALC300 130 
#define  ALC269_TYPE_ALC623 129 
#define  ALC269_TYPE_ALC700 128 
 int alc_parse_auto_config (struct hda_codec*,int const*,int const*) ; 

__attribute__((used)) static int alc269_parse_auto_config(struct hda_codec *codec)
{
	static const hda_nid_t alc269_ignore[] = { 0x1d, 0 };
	static const hda_nid_t alc269_ssids[] = { 0, 0x1b, 0x14, 0x21 };
	static const hda_nid_t alc269va_ssids[] = { 0x15, 0x1b, 0x14, 0 };
	struct alc_spec *spec = codec->spec;
	const hda_nid_t *ssids;

	switch (spec->codec_variant) {
	case ALC269_TYPE_ALC269VA:
	case ALC269_TYPE_ALC269VC:
	case ALC269_TYPE_ALC280:
	case ALC269_TYPE_ALC284:
	case ALC269_TYPE_ALC293:
		ssids = alc269va_ssids;
		break;
	case ALC269_TYPE_ALC269VB:
	case ALC269_TYPE_ALC269VD:
	case ALC269_TYPE_ALC282:
	case ALC269_TYPE_ALC283:
	case ALC269_TYPE_ALC286:
	case ALC269_TYPE_ALC298:
	case ALC269_TYPE_ALC255:
	case ALC269_TYPE_ALC256:
	case ALC269_TYPE_ALC257:
	case ALC269_TYPE_ALC215:
	case ALC269_TYPE_ALC225:
	case ALC269_TYPE_ALC294:
	case ALC269_TYPE_ALC300:
	case ALC269_TYPE_ALC623:
	case ALC269_TYPE_ALC700:
		ssids = alc269_ssids;
		break;
	default:
		ssids = alc269_ssids;
		break;
	}

	return alc_parse_auto_config(codec, alc269_ignore, ssids);
}