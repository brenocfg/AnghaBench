#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  proc_getname; } ;
struct trace {TYPE_1__ stats; int /*<<< orphan*/  live; scalar_t__ fd_path_disabled; } ;
struct TYPE_6__ {int max; TYPE_2__* table; } ;
struct thread_trace {TYPE_3__ files; } ;
struct thread {int dummy; } ;
struct TYPE_5__ {char const* pathname; } ;

/* Variables and functions */
 struct thread_trace* thread__priv (struct thread*) ; 
 scalar_t__ thread__read_fd_path (struct thread*,int) ; 

__attribute__((used)) static const char *thread__fd_path(struct thread *thread, int fd,
				   struct trace *trace)
{
	struct thread_trace *ttrace = thread__priv(thread);

	if (ttrace == NULL || trace->fd_path_disabled)
		return NULL;

	if (fd < 0)
		return NULL;

	if ((fd > ttrace->files.max || ttrace->files.table[fd].pathname == NULL)) {
		if (!trace->live)
			return NULL;
		++trace->stats.proc_getname;
		if (thread__read_fd_path(thread, fd))
			return NULL;
	}

	return ttrace->files.table[fd].pathname;
}