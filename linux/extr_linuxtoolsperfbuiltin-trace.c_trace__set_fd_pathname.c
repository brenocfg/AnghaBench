#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int max; char** table; } ;
struct thread_trace {TYPE_1__ paths; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,int) ; 
 char** realloc (char**,int) ; 
 char* strdup (char const*) ; 
 struct thread_trace* thread__priv (struct thread*) ; 

__attribute__((used)) static int trace__set_fd_pathname(struct thread *thread, int fd, const char *pathname)
{
	struct thread_trace *ttrace = thread__priv(thread);

	if (fd > ttrace->paths.max) {
		char **npath = realloc(ttrace->paths.table, (fd + 1) * sizeof(char *));

		if (npath == NULL)
			return -1;

		if (ttrace->paths.max != -1) {
			memset(npath + ttrace->paths.max + 1, 0,
			       (fd - ttrace->paths.max) * sizeof(char *));
		} else {
			memset(npath, 0, (fd + 1) * sizeof(char *));
		}

		ttrace->paths.table = npath;
		ttrace->paths.max   = fd;
	}

	ttrace->paths.table[fd] = strdup(pathname);

	return ttrace->paths.table[fd] != NULL ? 0 : -1;
}