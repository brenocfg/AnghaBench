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
struct hda_jack_callback {scalar_t__ nid; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_pin_power_jack (struct hda_codec*,scalar_t__,int) ; 
 int /*<<< orphan*/  sync_power_state_change (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pin_power_callback(struct hda_codec *codec,
			       struct hda_jack_callback *jack,
			       bool on)
{
	if (jack && jack->nid)
		sync_power_state_change(codec,
					set_pin_power_jack(codec, jack->nid, on));
}