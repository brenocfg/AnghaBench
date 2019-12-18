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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  st64 ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 char* cmd_syscall_dostr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_println (char*) ; 

__attribute__((used)) static void cmd_syscall_do(RCore *core, st64 n, ut64 addr) {
	char *msg = cmd_syscall_dostr (core, n, addr);
	if (msg) {
		r_cons_println (msg);
		free (msg);
	}
}