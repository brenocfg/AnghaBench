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
struct pipe_inode_info {int readers; int /*<<< orphan*/  writers; int /*<<< orphan*/  wait; int /*<<< orphan*/  fasync_readers; } ;
struct file {struct pipe_inode_info* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_lock (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  pipe_unlock (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wait_for_dump_helpers(struct file *file)
{
	struct pipe_inode_info *pipe = file->private_data;

	pipe_lock(pipe);
	pipe->readers++;
	pipe->writers--;
	wake_up_interruptible_sync(&pipe->wait);
	kill_fasync(&pipe->fasync_readers, SIGIO, POLL_IN);
	pipe_unlock(pipe);

	/*
	 * We actually want wait_event_freezable() but then we need
	 * to clear TIF_SIGPENDING and improve dump_interrupted().
	 */
	wait_event_interruptible(pipe->wait, pipe->readers == 1);

	pipe_lock(pipe);
	pipe->readers--;
	pipe->writers++;
	pipe_unlock(pipe);
}