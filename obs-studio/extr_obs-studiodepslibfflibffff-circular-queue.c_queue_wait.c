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
struct ff_circular_queue {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void queue_wait(struct ff_circular_queue *cq)
{
	pthread_cond_wait(&cq->cond, &cq->mutex);
}