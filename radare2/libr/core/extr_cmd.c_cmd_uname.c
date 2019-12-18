#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/  sysname; } ;
typedef  TYPE_1__ RSysInfo ;

/* Variables and functions */
 int /*<<< orphan*/  r_cons_newline () ; 
 int /*<<< orphan*/  r_cons_printf (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* r_sys_info () ; 
 int /*<<< orphan*/  r_sys_info_free (TYPE_1__*) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static int cmd_uname(void *data, const char *input) { // "uniq"
	RSysInfo *si = r_sys_info();
	if (si) {
		r_cons_printf ("%s", si->sysname);
		if (strstr (input, "-r")) {
			r_cons_printf (" %s", si->release);
		}
		r_cons_newline ();
		r_sys_info_free (si);
	}
	return 0;
}