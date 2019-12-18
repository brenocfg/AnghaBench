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
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentThread () ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ SetThreadPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_PRIORITY_HIGHEST ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_getschedpolicy (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  pthread_setschedprio (int /*<<< orphan*/ ,int) ; 
 int sched_get_priority_max (int) ; 
 int /*<<< orphan*/  stderr ; 

void
pixie_cpu_raise_priority(void)
{
#if defined WIN32
DWORD_PTR result;
    result = SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
    if (result == 0) {
        fprintf(stderr, "set_priority: returned error win32:%u\n", (unsigned)GetLastError());
    }
#elif defined(__linux__) && defined(__GNUC__)
    pthread_t thread = pthread_self();
    pthread_attr_t thAttr;
    int policy = 0;
    int max_prio_for_policy = 0;

    pthread_attr_init(&thAttr);
    pthread_attr_getschedpolicy(&thAttr, &policy);
    max_prio_for_policy = sched_get_priority_max(policy);


    pthread_setschedprio(thread, max_prio_for_policy);
    pthread_attr_destroy(&thAttr);
    return;

#endif
}