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
struct hda_jack_callback {int /*<<< orphan*/  nid; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_presence_and_report (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ codec_has_acomp (struct hda_codec*) ; 

__attribute__((used)) static void jack_callback(struct hda_codec *codec,
			  struct hda_jack_callback *jack)
{
	/* stop polling when notification is enabled */
	if (codec_has_acomp(codec))
		return;

	/* hda_jack don't support DP MST */
	check_presence_and_report(codec, jack->nid, 0);
}