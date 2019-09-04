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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_PARKED ; 
 int /*<<< orphan*/  MSG_UNPARKED ; 
 int /*<<< orphan*/  spk_msg_get (int /*<<< orphan*/ ) ; 
 int spk_parked ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void speakup_parked(struct vc_data *vc)
{
	if (spk_parked & 0x80) {
		spk_parked = 0;
		synth_printf("%s\n", spk_msg_get(MSG_UNPARKED));
	} else {
		spk_parked |= 0x80;
		synth_printf("%s\n", spk_msg_get(MSG_PARKED));
	}
}