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

/* Variables and functions */
 int /*<<< orphan*/  SUSPEND_CONSOLE ; 
 scalar_t__ orig_fgconsole ; 
 int /*<<< orphan*/  orig_kmsg ; 
 int /*<<< orphan*/  pm_vt_switch () ; 
 int /*<<< orphan*/  vt_kmsg_redirect (int /*<<< orphan*/ ) ; 
 scalar_t__ vt_move_to_console (int /*<<< orphan*/ ,int) ; 

void pm_prepare_console(void)
{
	if (!pm_vt_switch())
		return;

	orig_fgconsole = vt_move_to_console(SUSPEND_CONSOLE, 1);
	if (orig_fgconsole < 0)
		return;

	orig_kmsg = vt_kmsg_redirect(SUSPEND_CONSOLE);
	return;
}