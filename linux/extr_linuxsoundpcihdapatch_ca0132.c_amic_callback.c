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
struct ca0132_spec {scalar_t__ use_alt_functions; } ;

/* Variables and functions */
 int /*<<< orphan*/  ca0132_alt_select_in (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_select_mic (struct hda_codec*) ; 

__attribute__((used)) static void amic_callback(struct hda_codec *codec, struct hda_jack_callback *cb)
{
	struct ca0132_spec *spec = codec->spec;

	if (spec->use_alt_functions)
		ca0132_alt_select_in(codec);
	else
		ca0132_select_mic(codec);
}