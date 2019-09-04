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
struct vcs_poll_data {int /*<<< orphan*/  fasync; } ;
struct file {struct vcs_poll_data* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 
 struct vcs_poll_data* vcs_poll_data_get (struct file*) ; 

__attribute__((used)) static int
vcs_fasync(int fd, struct file *file, int on)
{
	struct vcs_poll_data *poll = file->private_data;

	if (!poll) {
		/* don't allocate anything if all we want is disable fasync */
		if (!on)
			return 0;
		poll = vcs_poll_data_get(file);
		if (!poll)
			return -ENOMEM;
	}

	return fasync_helper(fd, file, on, &poll->fasync);
}