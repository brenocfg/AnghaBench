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
struct sched_param {int /*<<< orphan*/  sched_priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCHED_IDLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  job_thread ; 
 int /*<<< orphan*/  jobs ; 
 int /*<<< orphan*/  list_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwan_status_critical_perror (char*) ; 
 int /*<<< orphan*/  lwan_status_debug (char*) ; 
 int /*<<< orphan*/  lwan_status_perror (char*) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_setschedparam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 int running ; 
 int /*<<< orphan*/  self ; 

void lwan_job_thread_init(void)
{
    assert(!running);

    lwan_status_debug("Initializing low priority job thread");

    list_head_init(&jobs);

    running = true;
    if (pthread_create(&self, NULL, job_thread, NULL) < 0)
        lwan_status_critical_perror("pthread_create");

#ifdef SCHED_IDLE
    struct sched_param sched_param = {
        .sched_priority = 0
    };
    if (pthread_setschedparam(self, SCHED_IDLE, &sched_param) < 0)
        lwan_status_perror("pthread_setschedparam");
#endif  /* SCHED_IDLE */
}