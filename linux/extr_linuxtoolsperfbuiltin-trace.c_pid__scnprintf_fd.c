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
struct trace {int /*<<< orphan*/  host; } ;
struct thread {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 struct thread* machine__find_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t scnprintf (char*,size_t,char*,...) ; 
 char* thread__fd_path (struct thread*,int,struct trace*) ; 
 int /*<<< orphan*/  thread__put (struct thread*) ; 

size_t pid__scnprintf_fd(struct trace *trace, pid_t pid, int fd, char *bf, size_t size)
{
        size_t printed = scnprintf(bf, size, "%d", fd);
	struct thread *thread = machine__find_thread(trace->host, pid, pid);

	if (thread) {
		const char *path = thread__fd_path(thread, fd, trace);

		if (path)
			printed += scnprintf(bf + printed, size - printed, "<%s>", path);

		thread__put(thread);
	}

        return printed;
}