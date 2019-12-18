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
struct defer_call {int /*<<< orphan*/  cb; int /*<<< orphan*/  (* call ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  circlebuf_pop_front (int /*<<< orphan*/ *,struct defer_call*,int) ; 
 scalar_t__ defer_call_exit ; 
 int /*<<< orphan*/  defer_call_mutex ; 
 int /*<<< orphan*/  defer_call_queue ; 
 int /*<<< orphan*/  defer_call_semaphore ; 
 scalar_t__ os_sem_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *defer_thread(void *unused)
{
	UNUSED_PARAMETER(unused);

	while (os_sem_wait(defer_call_semaphore) == 0) {
		struct defer_call info;

		pthread_mutex_lock(&defer_call_mutex);
		if (defer_call_exit) {
			pthread_mutex_unlock(&defer_call_mutex);
			return NULL;
		}

		circlebuf_pop_front(&defer_call_queue, &info, sizeof(info));
		pthread_mutex_unlock(&defer_call_mutex);

		info.call(info.cb);
	}

	return NULL;
}