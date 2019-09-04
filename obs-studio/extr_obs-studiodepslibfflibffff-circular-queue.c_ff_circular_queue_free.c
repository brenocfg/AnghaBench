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
struct ff_circular_queue {int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_circular_queue_abort (struct ff_circular_queue*) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void ff_circular_queue_free(struct ff_circular_queue *cq)
{
	ff_circular_queue_abort(cq);

	if (cq->slots != NULL)
		av_free(cq->slots);

	pthread_mutex_destroy(&cq->mutex);
	pthread_cond_destroy(&cq->cond);
}