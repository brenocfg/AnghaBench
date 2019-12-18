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
struct trace_iterator {int /*<<< orphan*/  mutex; scalar_t__ pos; int /*<<< orphan*/  tr; } ;
struct file {int f_flags; struct trace_iterator* private_data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ trace_empty (struct trace_iterator*) ; 
 int /*<<< orphan*/  tracer_tracing_is_on (int /*<<< orphan*/ ) ; 
 int wait_on_pipe (struct trace_iterator*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tracing_wait_pipe(struct file *filp)
{
	struct trace_iterator *iter = filp->private_data;
	int ret;

	while (trace_empty(iter)) {

		if ((filp->f_flags & O_NONBLOCK)) {
			return -EAGAIN;
		}

		/*
		 * We block until we read something and tracing is disabled.
		 * We still block if tracing is disabled, but we have never
		 * read anything. This allows a user to cat this file, and
		 * then enable tracing. But after we have read something,
		 * we give an EOF when tracing is again disabled.
		 *
		 * iter->pos will be 0 if we haven't read anything.
		 */
		if (!tracer_tracing_is_on(iter->tr) && iter->pos)
			break;

		mutex_unlock(&iter->mutex);

		ret = wait_on_pipe(iter, 0);

		mutex_lock(&iter->mutex);

		if (ret)
			return ret;
	}

	return 1;
}