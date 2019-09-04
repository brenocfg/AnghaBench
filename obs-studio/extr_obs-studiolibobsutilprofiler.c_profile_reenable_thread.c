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

/* Variables and functions */
 scalar_t__ enabled ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  root_mutex ; 
 scalar_t__ thread_enabled ; 

void profile_reenable_thread(void)
{
	if (thread_enabled)
		return;

	pthread_mutex_lock(&root_mutex);
	thread_enabled = enabled;
	pthread_mutex_unlock(&root_mutex);
}