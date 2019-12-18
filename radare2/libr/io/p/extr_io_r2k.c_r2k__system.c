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
typedef  int /*<<< orphan*/  RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemModules (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  run_ioctl_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static char *r2k__system(RIO *io, RIODesc *fd, const char *cmd) {
	if (!strcmp (cmd, "")) {
		return NULL;
	}
	if (!strncmp (cmd, "mod", 3)) {
#if __WINDOWS__
		GetSystemModules (io);
#endif
	} else {
#if defined (__linux__) && !defined (__GNU__)
		(void)run_ioctl_command (io, fd, cmd);
		return NULL;
#else
		eprintf ("Try: '=!mod'\n    '.=!mod'\n");
#endif
	}
	return NULL;
}