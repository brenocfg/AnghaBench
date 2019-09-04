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
 int /*<<< orphan*/  alc_update_coef_idx (struct hda_codec*,int,int,int) ; 

__attribute__((used)) static void alc269vb_toggle_power_output(struct hda_codec *codec, int power_up)
{
	alc_update_coef_idx(codec, 0x04, 1 << 11, power_up ? (1 << 11) : 0);
}