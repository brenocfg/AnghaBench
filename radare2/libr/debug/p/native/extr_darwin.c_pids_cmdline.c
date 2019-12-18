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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int pids_cmdline(int pid, char *cmdline) {
        int fd;
        sprintf(cmdline, "/proc/%d/cmdline", pid);
        fd = open(cmdline, O_RDONLY);
        cmdline[0] = '\0';
        if (fd != -1) {
                read(fd, cmdline, 1024);
                cmdline[1024] = '\0';
                close(fd);
        }

        return 0;
}