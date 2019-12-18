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
struct m_thread_info {int /*<<< orphan*/  handle; void* res; } ;

/* Variables and functions */
 int /*<<< orphan*/  ExitThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (struct m_thread_info*) ; 
 struct m_thread_info* find_thread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  pthread_table_lock ; 
 int /*<<< orphan*/  remove_thread_info (struct m_thread_info*) ; 

void pthread_exit(void *retval)
{
    pthread_mutex_lock(&pthread_table_lock);
    struct m_thread_info *info = find_thread_info(pthread_self());
    assert(info); // not started with pthread_create, or pthread_join() race
    info->res = retval;
    if (!info->handle)
        remove_thread_info(info); // detached case
    pthread_mutex_unlock(&pthread_table_lock);

    ExitThread(0);
}