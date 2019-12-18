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
struct sbq_wait {int /*<<< orphan*/  wait; struct sbitmap_queue* sbq; } ;
struct sbitmap_queue {int /*<<< orphan*/  ws_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

void sbitmap_add_wait_queue(struct sbitmap_queue *sbq,
			    struct sbq_wait_state *ws,
			    struct sbq_wait *sbq_wait)
{
	if (!sbq_wait->sbq) {
		sbq_wait->sbq = sbq;
		atomic_inc(&sbq->ws_active);
	}
	add_wait_queue(&ws->wait, &sbq_wait->wait);
}