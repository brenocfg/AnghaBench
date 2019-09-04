#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  proc_getname; } ;
struct trace {TYPE_1__ stats; int /*<<< orphan*/  live; } ;
struct TYPE_4__ {int max; char const** table; } ;
struct thread_trace {TYPE_2__ paths; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 struct thread_trace* thread__priv (struct thread*) ; 
 scalar_t__ thread__read_fd_path (struct thread*,int) ; 

__attribute__((used)) static const char *thread__fd_path(struct thread *thread, int fd,
				   struct trace *trace)
{
	struct thread_trace *ttrace = thread__priv(thread);

	if (ttrace == NULL)
		return NULL;

	if (fd < 0)
		return NULL;

	if ((fd > ttrace->paths.max || ttrace->paths.table[fd] == NULL)) {
		if (!trace->live)
			return NULL;
		++trace->stats.proc_getname;
		if (thread__read_fd_path(thread, fd))
			return NULL;
	}

	return ttrace->paths.table[fd];
}