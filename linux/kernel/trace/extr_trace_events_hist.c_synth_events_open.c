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
struct inode {int dummy; } ;
struct file {int f_mode; int f_flags; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  LOCKDOWN_TRACEFS ; 
 int O_TRUNC ; 
 int dyn_events_release_all (int /*<<< orphan*/ *) ; 
 int security_locked_down (int /*<<< orphan*/ ) ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synth_event_ops ; 
 int /*<<< orphan*/  synth_events_seq_op ; 

__attribute__((used)) static int synth_events_open(struct inode *inode, struct file *file)
{
	int ret;

	ret = security_locked_down(LOCKDOWN_TRACEFS);
	if (ret)
		return ret;

	if ((file->f_mode & FMODE_WRITE) && (file->f_flags & O_TRUNC)) {
		ret = dyn_events_release_all(&synth_event_ops);
		if (ret < 0)
			return ret;
	}

	return seq_open(file, &synth_events_seq_op);
}