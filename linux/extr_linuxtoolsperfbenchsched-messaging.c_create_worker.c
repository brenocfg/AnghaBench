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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  PTHREAD_STACK_MIN ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 scalar_t__ pthread_attr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_setstacksize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),void*) ; 
 void* stub1 (void*) ; 
 int /*<<< orphan*/  thread_mode ; 

__attribute__((used)) static pthread_t create_worker(void *ctx, void *(*func)(void *))
{
	pthread_attr_t attr;
	pthread_t childid;
	int ret;

	if (!thread_mode) {
		/* process mode */
		/* Fork the receiver. */
		switch (fork()) {
		case -1:
			err(EXIT_FAILURE, "fork()");
			break;
		case 0:
			(*func) (ctx);
			exit(0);
			break;
		default:
			break;
		}

		return (pthread_t)0;
	}

	if (pthread_attr_init(&attr) != 0)
		err(EXIT_FAILURE, "pthread_attr_init:");

#ifndef __ia64__
	if (pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN) != 0)
		err(EXIT_FAILURE, "pthread_attr_setstacksize");
#endif

	ret = pthread_create(&childid, &attr, func, ctx);
	if (ret != 0)
		err(EXIT_FAILURE, "pthread_create failed");

	return childid;
}