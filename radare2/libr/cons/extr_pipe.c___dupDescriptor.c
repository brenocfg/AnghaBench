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
 int /*<<< orphan*/  _SC_OPEN_MAX ; 
 int _dup2 (int,int) ; 
 int backup_fd ; 
 int dup2 (int,int) ; 
 int sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __dupDescriptor(int fd, int fdn) {
#if __WINDOWS__
	backup_fd = 2002 - (fd - 2); // windows xp has 2048 as limit fd
	return _dup2 (fdn, backup_fd) != -1;
#else
	backup_fd = sysconf (_SC_OPEN_MAX) - (fd - 2); // portable getdtablesize()
	if (backup_fd < 2) {
		backup_fd = 2002 - (fd - 2); // fallback
	}
	return dup2 (fdn, backup_fd) != -1;
#endif
}