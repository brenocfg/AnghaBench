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
 int EINVAL ; 
 int PF_FL_RW ; 
 int open_kprobe_events (int) ; 
 int open_uprobe_events (int) ; 
 int /*<<< orphan*/  print_both_open_warning (int,int) ; 

int probe_file__open_both(int *kfd, int *ufd, int flag)
{
	if (!kfd || !ufd)
		return -EINVAL;

	*kfd = open_kprobe_events(flag & PF_FL_RW);
	*ufd = open_uprobe_events(flag & PF_FL_RW);
	if (*kfd < 0 && *ufd < 0) {
		print_both_open_warning(*kfd, *ufd);
		return *kfd;
	}

	return 0;
}