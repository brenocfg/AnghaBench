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
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_GOTO ; 
 scalar_t__ handle_goto ; 
 int /*<<< orphan*/  spk_msg_get (int /*<<< orphan*/ ) ; 
 scalar_t__ spk_special_handler ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void speakup_goto(struct vc_data *vc)
{
	if (spk_special_handler) {
		synth_printf("%s\n", spk_msg_get(MSG_ERROR));
		return;
	}
	synth_printf("%s\n", spk_msg_get(MSG_GOTO));
	spk_special_handler = handle_goto;
}