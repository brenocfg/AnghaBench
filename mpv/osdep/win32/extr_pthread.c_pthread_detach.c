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
struct m_thread_info {struct m_thread_info* handle; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (struct m_thread_info*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (struct m_thread_info*) ; 
 struct m_thread_info* find_thread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  pthread_table_lock ; 

int pthread_detach(pthread_t thread)
{
    if (!pthread_equal(thread, pthread_self()))
        abort(); // restriction of this wrapper

    pthread_mutex_lock(&pthread_table_lock);
    struct m_thread_info *info = find_thread_info(thread);
    assert(info); // not started with pthread_create
    assert(info->handle); // already detached
    CloseHandle(info->handle);
    info->handle = NULL;
    pthread_mutex_unlock(&pthread_table_lock);

    return 0;
}