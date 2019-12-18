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
typedef  int /*<<< orphan*/ * pthread_mutex_t ;

/* Variables and functions */
 int InterlockedExchange (long*,int) ; 
 int /*<<< orphan*/  PGTHREAD_ERROR (char*) ; 
 int /*<<< orphan*/ * PTHREAD_MUTEX_INITIALIZER ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ **) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
default_threadlock(int acquire)
{
#ifdef ENABLE_THREAD_SAFETY
#ifndef WIN32
	static pthread_mutex_t singlethread_lock = PTHREAD_MUTEX_INITIALIZER;
#else
	static pthread_mutex_t singlethread_lock = NULL;
	static long mutex_initlock = 0;

	if (singlethread_lock == NULL)
	{
		while (InterlockedExchange(&mutex_initlock, 1) == 1)
			 /* loop, another thread own the lock */ ;
		if (singlethread_lock == NULL)
		{
			if (pthread_mutex_init(&singlethread_lock, NULL))
				PGTHREAD_ERROR("failed to initialize mutex");
		}
		InterlockedExchange(&mutex_initlock, 0);
	}
#endif
	if (acquire)
	{
		if (pthread_mutex_lock(&singlethread_lock))
			PGTHREAD_ERROR("failed to lock mutex");
	}
	else
	{
		if (pthread_mutex_unlock(&singlethread_lock))
			PGTHREAD_ERROR("failed to unlock mutex");
	}
#endif
}