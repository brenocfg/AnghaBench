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
struct job {int (* cb ) (void*) ;int /*<<< orphan*/  jobs; void* data; } ;

/* Variables and functions */
 scalar_t__ LIKELY (int) ; 
 int /*<<< orphan*/  assert (int (*) (void*)) ; 
 struct job* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct job*) ; 
 int /*<<< orphan*/  jobs ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwan_status_critical_perror (char*) ; 
 int /*<<< orphan*/  lwan_status_warning (char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_mutex ; 

void lwan_job_add(bool (*cb)(void *data), void *data)
{
    assert(cb);

    struct job *job = calloc(1, sizeof(*job));
    if (!job)
        lwan_status_critical_perror("calloc");

    job->cb = cb;
    job->data = data;

    if (LIKELY(!pthread_mutex_lock(&queue_mutex))) {
        list_add(&jobs, &job->jobs);
        pthread_mutex_unlock(&queue_mutex);
    } else {
        lwan_status_warning("Couldn't lock job mutex");
        free(job);
    }
}