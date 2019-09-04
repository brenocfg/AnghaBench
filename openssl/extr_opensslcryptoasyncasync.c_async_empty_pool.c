#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  jobs; } ;
typedef  TYPE_1__ async_pool ;
typedef  int /*<<< orphan*/  ASYNC_JOB ;

/* Variables and functions */
 int /*<<< orphan*/  async_job_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_ASYNC_JOB_pop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void async_empty_pool(async_pool *pool)
{
    ASYNC_JOB *job;

    if (!pool || !pool->jobs)
        return;

    do {
        job = sk_ASYNC_JOB_pop(pool->jobs);
        async_job_free(job);
    } while (job);
}