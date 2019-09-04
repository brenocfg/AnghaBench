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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int (* pin_hbr_setup ) (struct hda_codec*,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct hdmi_spec {TYPE_1__ ops; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_DIG3_ICT ; 
 int /*<<< orphan*/  AC_VERB_GET_DIGI_CONVERT_1 ; 
 int /*<<< orphan*/  AC_VERB_SET_DIGI_CONVERT_3 ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 
 scalar_t__ is_haswell_plus (struct hda_codec*) ; 
 scalar_t__ is_hbr_format (int) ; 
 unsigned int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_setup_stream (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int stub1 (struct hda_codec*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int hdmi_setup_stream(struct hda_codec *codec, hda_nid_t cvt_nid,
			      hda_nid_t pin_nid, u32 stream_tag, int format)
{
	struct hdmi_spec *spec = codec->spec;
	unsigned int param;
	int err;

	err = spec->ops.pin_hbr_setup(codec, pin_nid, is_hbr_format(format));

	if (err) {
		codec_dbg(codec, "hdmi_setup_stream: HBR is not supported\n");
		return err;
	}

	if (is_haswell_plus(codec)) {

		/*
		 * on recent platforms IEC Coding Type is required for HBR
		 * support, read current Digital Converter settings and set
		 * ICT bitfield if needed.
		 */
		param = snd_hda_codec_read(codec, cvt_nid, 0,
					   AC_VERB_GET_DIGI_CONVERT_1, 0);

		param = (param >> 16) & ~(AC_DIG3_ICT);

		/* on recent platforms ICT mode is required for HBR support */
		if (is_hbr_format(format))
			param |= 0x1;

		snd_hda_codec_write(codec, cvt_nid, 0,
				    AC_VERB_SET_DIGI_CONVERT_3, param);
	}

	snd_hda_codec_setup_stream(codec, cvt_nid, stream_tag, 0, format);
	return 0;
}