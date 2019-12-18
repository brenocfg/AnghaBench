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
 int /*<<< orphan*/  __set (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  def_msgs ; 
 int /*<<< orphan*/  def_msgsize ; 
 scalar_t__ default_settings ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_msgs ; 
 int /*<<< orphan*/  max_msgsize ; 
 scalar_t__ mq_close (int) ; 
 int /*<<< orphan*/  mq_unlink (scalar_t__) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int queue ; 
 scalar_t__ queue_path ; 
 scalar_t__ saved_def_msgs ; 
 scalar_t__ saved_def_msgsize ; 
 scalar_t__ saved_max_msgs ; 
 scalar_t__ saved_max_msgsize ; 
 int seteuid (int /*<<< orphan*/ ) ; 

void shutdown(int exit_val, char *err_cause, int line_no)
{
	static int in_shutdown = 0;

	/* In case we get called recursively by a set() call below */
	if (in_shutdown++)
		return;

	if (seteuid(0) == -1)
		perror("seteuid() failed");

	if (queue != -1)
		if (mq_close(queue))
			perror("mq_close() during shutdown");
	if (queue_path)
		/*
		 * Be silent if this fails, if we cleaned up already it's
		 * expected to fail
		 */
		mq_unlink(queue_path);
	if (default_settings) {
		if (saved_def_msgs)
			__set(def_msgs, saved_def_msgs,
			      "failed to restore saved_def_msgs");
		if (saved_def_msgsize)
			__set(def_msgsize, saved_def_msgsize,
			      "failed to restore saved_def_msgsize");
	}
	if (saved_max_msgs)
		__set(max_msgs, saved_max_msgs,
		      "failed to restore saved_max_msgs");
	if (saved_max_msgsize)
		__set(max_msgsize, saved_max_msgsize,
		      "failed to restore saved_max_msgsize");
	if (exit_val)
		error(exit_val, errno, "%s at %d", err_cause, line_no);
	exit(0);
}