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
struct thread_data {int /*<<< orphan*/ * ready; int /*<<< orphan*/  pt; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 scalar_t__ pipe (int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct thread_data*) ; 
 int read (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  thread_fn ; 
 struct thread_data* threads ; 

__attribute__((used)) static int thread_create(int i)
{
	struct thread_data *td = &threads[i];
	int err, go;

	if (pipe(td->ready))
		return -1;

	err = pthread_create(&td->pt, NULL, thread_fn, td);
	if (!err) {
		/* Wait for thread initialization. */
		ssize_t ret = read(td->ready[0], &go, sizeof(int));
		err = ret != sizeof(int);
	}

	close(td->ready[0]);
	close(td->ready[1]);
	return err;
}