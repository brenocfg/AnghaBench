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
struct sbq_wait_state {int /*<<< orphan*/  wait; } ;
struct sbq_wait {int /*<<< orphan*/ * sbq; int /*<<< orphan*/  wait; } ;
struct sbitmap_queue {int /*<<< orphan*/  ws_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void sbitmap_finish_wait(struct sbitmap_queue *sbq, struct sbq_wait_state *ws,
			 struct sbq_wait *sbq_wait)
{
	finish_wait(&ws->wait, &sbq_wait->wait);
	if (sbq_wait->sbq) {
		atomic_dec(&sbq->ws_active);
		sbq_wait->sbq = NULL;
	}
}