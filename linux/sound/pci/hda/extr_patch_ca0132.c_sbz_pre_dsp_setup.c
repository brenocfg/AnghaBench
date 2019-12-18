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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {scalar_t__ mem_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_PIN_WIDGET_CONTROL ; 
 int /*<<< orphan*/  chipio_write (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sbz_pre_dsp_setup(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;

	writel(0x00820680, spec->mem_base + 0x01C);
	writel(0x00820680, spec->mem_base + 0x01C);

	chipio_write(codec, 0x18b0a4, 0x000000c2);

	snd_hda_codec_write(codec, 0x11, 0,
			AC_VERB_SET_PIN_WIDGET_CONTROL, 0x44);
}