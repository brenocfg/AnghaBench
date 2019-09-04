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
typedef  int u64 ;
struct uac3_as_header_descriptor {int /*<<< orphan*/  bmFormats; } ;
struct snd_usb_audio {int dummy; } ;
struct audioformat {int /*<<< orphan*/  fmt_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  UAC_FORMAT_TYPE_I ; 
 int /*<<< orphan*/  UAC_FORMAT_TYPE_III ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int parse_audio_format_i (struct snd_usb_audio*,struct audioformat*,int,struct uac3_as_header_descriptor*) ; 

int snd_usb_parse_audio_format_v3(struct snd_usb_audio *chip,
			       struct audioformat *fp,
			       struct uac3_as_header_descriptor *as,
			       int stream)
{
	u64 format = le64_to_cpu(as->bmFormats);
	int err;

	/*
	 * Type I format bits are D0..D6
	 * This test works because type IV is not supported
	 */
	if (format & 0x7f)
		fp->fmt_type = UAC_FORMAT_TYPE_I;
	else
		fp->fmt_type = UAC_FORMAT_TYPE_III;

	err = parse_audio_format_i(chip, fp, format, as);
	if (err < 0)
		return err;

	return 0;
}