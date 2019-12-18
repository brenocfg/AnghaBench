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
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  job_wait_cond ; 
 int /*<<< orphan*/  job_wait_mutex ; 
 int /*<<< orphan*/  pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 

__attribute__((used)) static void
timedwait(bool had_job)
{
    static int secs = 1;
    struct timeval now;

    if (had_job)
        secs = 1;
    else if (secs <= 15)
        secs++;

    gettimeofday(&now, NULL);

    struct timespec rgtp = { now.tv_sec + secs, now.tv_usec * 1000 };
    pthread_cond_timedwait(&job_wait_cond, &job_wait_mutex, &rgtp);
}