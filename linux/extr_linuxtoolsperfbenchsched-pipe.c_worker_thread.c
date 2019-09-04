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
struct thread_data {int /*<<< orphan*/  pipe_read; int /*<<< orphan*/  pipe_write; int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int loops ; 
 int read (int /*<<< orphan*/ ,int*,int) ; 
 int write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void *worker_thread(void *__tdata)
{
	struct thread_data *td = __tdata;
	int m = 0, i;
	int ret;

	for (i = 0; i < loops; i++) {
		if (!td->nr) {
			ret = read(td->pipe_read, &m, sizeof(int));
			BUG_ON(ret != sizeof(int));
			ret = write(td->pipe_write, &m, sizeof(int));
			BUG_ON(ret != sizeof(int));
		} else {
			ret = write(td->pipe_write, &m, sizeof(int));
			BUG_ON(ret != sizeof(int));
			ret = read(td->pipe_read, &m, sizeof(int));
			BUG_ON(ret != sizeof(int));
		}
	}

	return NULL;
}