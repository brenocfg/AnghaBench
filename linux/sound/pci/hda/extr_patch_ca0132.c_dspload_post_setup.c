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
struct ca0132_spec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XRAM_XRAM_INST_OFFSET (int) ; 
 int /*<<< orphan*/  ca0132_use_alt_functions (struct ca0132_spec*) ; 
 int /*<<< orphan*/  chipio_write (struct hda_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 

__attribute__((used)) static void dspload_post_setup(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	codec_dbg(codec, "---- dspload_post_setup ------\n");
	if (!ca0132_use_alt_functions(spec)) {
		/*set DSP speaker to 2.0 configuration*/
		chipio_write(codec, XRAM_XRAM_INST_OFFSET(0x18), 0x08080080);
		chipio_write(codec, XRAM_XRAM_INST_OFFSET(0x19), 0x3f800000);

		/*update write pointer*/
		chipio_write(codec, XRAM_XRAM_INST_OFFSET(0x29), 0x00000002);
	}
}