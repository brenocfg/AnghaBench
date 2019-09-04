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
struct hda_codec {int /*<<< orphan*/  power_save_node; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int detect_pin_state (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_path_power (struct hda_codec*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static hda_nid_t set_pin_power_jack(struct hda_codec *codec, hda_nid_t pin,
				    int power)
{
	bool on;

	if (!codec->power_save_node)
		return 0;

	on = detect_pin_state(codec, pin);

	if (power >= 0 && on != power)
		return 0;
	return set_path_power(codec, pin, on, -1);
}