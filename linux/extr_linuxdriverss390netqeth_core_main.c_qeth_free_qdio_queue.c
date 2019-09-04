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
struct qeth_qdio_q {int /*<<< orphan*/  qdio_bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  kfree (struct qeth_qdio_q*) ; 
 int /*<<< orphan*/  qdio_free_buffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qeth_free_qdio_queue(struct qeth_qdio_q *q)
{
	if (!q)
		return;

	qdio_free_buffers(q->qdio_bufs, QDIO_MAX_BUFFERS_PER_Q);
	kfree(q);
}