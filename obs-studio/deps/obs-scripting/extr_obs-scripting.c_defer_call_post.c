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
struct defer_call {void* cb; int /*<<< orphan*/  call; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  defer_call_cb ;

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_push_back (int /*<<< orphan*/ *,struct defer_call*,int) ; 
 int /*<<< orphan*/  defer_call_exit ; 
 int /*<<< orphan*/  defer_call_mutex ; 
 int /*<<< orphan*/  defer_call_queue ; 
 int /*<<< orphan*/  defer_call_semaphore ; 
 int /*<<< orphan*/  os_sem_post (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void defer_call_post(defer_call_cb call, void *cb)
{
	struct defer_call info;
	info.call = call;
	info.cb = cb;

	pthread_mutex_lock(&defer_call_mutex);
	if (!defer_call_exit)
		circlebuf_push_back(&defer_call_queue, &info, sizeof(info));
	pthread_mutex_unlock(&defer_call_mutex);

	os_sem_post(defer_call_semaphore);
}