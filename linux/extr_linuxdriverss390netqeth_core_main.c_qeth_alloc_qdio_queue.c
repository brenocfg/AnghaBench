#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qeth_qdio_q {int /*<<< orphan*/ * qdio_bufs; TYPE_1__* bufs; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,struct qeth_qdio_q**,int) ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  kfree (struct qeth_qdio_q*) ; 
 struct qeth_qdio_q* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ qdio_alloc_buffers (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct qeth_qdio_q *qeth_alloc_qdio_queue(void)
{
	struct qeth_qdio_q *q = kzalloc(sizeof(*q), GFP_KERNEL);
	int i;

	if (!q)
		return NULL;

	if (qdio_alloc_buffers(q->qdio_bufs, QDIO_MAX_BUFFERS_PER_Q)) {
		kfree(q);
		return NULL;
	}

	for (i = 0; i < QDIO_MAX_BUFFERS_PER_Q; ++i)
		q->bufs[i].buffer = q->qdio_bufs[i];

	QETH_DBF_HEX(SETUP, 2, &q, sizeof(void *));
	return q;
}