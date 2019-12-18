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
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  set_pin_target (struct hda_codec*,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static void set_pin_targets(struct hda_codec *codec, int num_pins,
			    hda_nid_t *pins, unsigned int val)
{
	int i;
	for (i = 0; i < num_pins; i++)
		set_pin_target(codec, pins[i], val, false);
}