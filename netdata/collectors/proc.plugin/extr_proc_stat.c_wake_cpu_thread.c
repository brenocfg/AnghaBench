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
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int pthread_setaffinity_np (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void* wake_cpu_thread(void* core) {
    pthread_t thread;
    cpu_set_t cpu_set;
    static size_t cpu_wakeups = 0;
    static int errors = 0;

    CPU_ZERO(&cpu_set);
    CPU_SET(*(int*)core, &cpu_set);

    thread = pthread_self();
    if(unlikely(pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpu_set))) {
        if(unlikely(errors < 8)) {
            error("Cannot set CPU affinity for core %d", *(int*)core);
            errors++;
        }
        else if(unlikely(errors < 9)) {
            error("CPU affinity errors are disabled");
            errors++;
        }
    }

    // Make the CPU core do something to force it to update its idle counters
    cpu_wakeups++;

    return 0;
}