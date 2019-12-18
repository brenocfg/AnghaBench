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
 int /*<<< orphan*/  r_cons_flush () ; 
 int /*<<< orphan*/  r_cons_set_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_sys_cmd (char*) ; 

int __system_shell_cb(void *user) {
	r_cons_set_raw (0);
	r_cons_flush ();
	r_sys_cmd ("$SHELL");
	return 0;
}