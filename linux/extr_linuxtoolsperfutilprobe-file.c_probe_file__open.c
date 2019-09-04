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
 int PF_FL_RW ; 
 int PF_FL_UPROBE ; 
 int open_kprobe_events (int) ; 
 int open_uprobe_events (int) ; 
 int /*<<< orphan*/  print_open_warning (int,int) ; 

int probe_file__open(int flag)
{
	int fd;

	if (flag & PF_FL_UPROBE)
		fd = open_uprobe_events(flag & PF_FL_RW);
	else
		fd = open_kprobe_events(flag & PF_FL_RW);
	if (fd < 0)
		print_open_warning(fd, flag & PF_FL_UPROBE);

	return fd;
}