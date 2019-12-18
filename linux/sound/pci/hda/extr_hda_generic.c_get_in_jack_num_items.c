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
struct hda_gen_spec {scalar_t__ add_jack_modes; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_vref_caps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int hweight32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_in_jack_num_items(struct hda_codec *codec, hda_nid_t pin)
{
	struct hda_gen_spec *spec = codec->spec;
	int nitems = 0;
	if (spec->add_jack_modes)
		nitems = hweight32(get_vref_caps(codec, pin));
	return nitems ? nitems : 1;
}