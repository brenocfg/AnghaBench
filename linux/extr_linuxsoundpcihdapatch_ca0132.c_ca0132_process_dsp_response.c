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
struct hda_jack_callback {int dummy; } ;
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {scalar_t__ wait_scp; } ;

/* Variables and functions */
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  dspio_clear_response_queue (struct hda_codec*) ; 
 scalar_t__ dspio_get_response_data (struct hda_codec*) ; 

__attribute__((used)) static void ca0132_process_dsp_response(struct hda_codec *codec,
					struct hda_jack_callback *callback)
{
	struct ca0132_spec *spec = codec->spec;

	codec_dbg(codec, "ca0132_process_dsp_response\n");
	if (spec->wait_scp) {
		if (dspio_get_response_data(codec) >= 0)
			spec->wait_scp = 0;
	}

	dspio_clear_response_queue(codec);
}