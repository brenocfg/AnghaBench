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
 scalar_t__ orig_fgconsole ; 
 int /*<<< orphan*/  orig_kmsg ; 
 int /*<<< orphan*/  pm_vt_switch () ; 
 int /*<<< orphan*/  vt_kmsg_redirect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt_move_to_console (scalar_t__,int /*<<< orphan*/ ) ; 

void pm_restore_console(void)
{
	if (!pm_vt_switch())
		return;

	if (orig_fgconsole >= 0) {
		vt_move_to_console(orig_fgconsole, 0);
		vt_kmsg_redirect(orig_kmsg);
	}
}