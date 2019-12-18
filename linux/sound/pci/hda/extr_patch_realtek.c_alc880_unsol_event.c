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

/* Variables and functions */
 int /*<<< orphan*/  snd_hda_jack_unsol_event (struct hda_codec*,unsigned int) ; 

__attribute__((used)) static void alc880_unsol_event(struct hda_codec *codec, unsigned int res)
{
	/* For some reason, the res given from ALC880 is broken.
	   Here we adjust it properly. */
	snd_hda_jack_unsol_event(codec, res >> 2);
}