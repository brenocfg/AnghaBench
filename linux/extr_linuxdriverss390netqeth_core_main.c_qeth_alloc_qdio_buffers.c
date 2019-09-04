#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct qeth_qdio_out_q {int dummy; } ;
struct TYPE_8__ {int no_out_queues; int /*<<< orphan*/  state; int /*<<< orphan*/ * in_q; TYPE_2__** out_qs; } ;
struct qeth_card {TYPE_1__ qdio; } ;
struct TYPE_9__ {int queue_no; int /*<<< orphan*/ ** bufs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,TYPE_2__**,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  QETH_QDIO_ALLOCATED ; 
 scalar_t__ QETH_QDIO_UNINITIALIZED ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__**) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ qeth_alloc_buffer_pool (struct qeth_card*) ; 
 scalar_t__ qeth_alloc_cq (struct qeth_card*) ; 
 TYPE_2__* qeth_alloc_qdio_out_buf () ; 
 int /*<<< orphan*/ * qeth_alloc_qdio_queue () ; 
 int /*<<< orphan*/  qeth_free_buffer_pool (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_free_output_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  qeth_free_qdio_queue (int /*<<< orphan*/ *) ; 
 scalar_t__ qeth_init_qdio_out_buf (TYPE_2__*,int) ; 
 int /*<<< orphan*/  qeth_qdio_outbuf_cache ; 

__attribute__((used)) static int qeth_alloc_qdio_buffers(struct qeth_card *card)
{
	int i, j;

	QETH_DBF_TEXT(SETUP, 2, "allcqdbf");

	if (atomic_cmpxchg(&card->qdio.state, QETH_QDIO_UNINITIALIZED,
		QETH_QDIO_ALLOCATED) != QETH_QDIO_UNINITIALIZED)
		return 0;

	QETH_DBF_TEXT(SETUP, 2, "inq");
	card->qdio.in_q = qeth_alloc_qdio_queue();
	if (!card->qdio.in_q)
		goto out_nomem;

	/* inbound buffer pool */
	if (qeth_alloc_buffer_pool(card))
		goto out_freeinq;

	/* outbound */
	card->qdio.out_qs =
		kcalloc(card->qdio.no_out_queues,
			sizeof(struct qeth_qdio_out_q *),
			GFP_KERNEL);
	if (!card->qdio.out_qs)
		goto out_freepool;
	for (i = 0; i < card->qdio.no_out_queues; ++i) {
		card->qdio.out_qs[i] = qeth_alloc_qdio_out_buf();
		if (!card->qdio.out_qs[i])
			goto out_freeoutq;
		QETH_DBF_TEXT_(SETUP, 2, "outq %i", i);
		QETH_DBF_HEX(SETUP, 2, &card->qdio.out_qs[i], sizeof(void *));
		card->qdio.out_qs[i]->queue_no = i;
		/* give outbound qeth_qdio_buffers their qdio_buffers */
		for (j = 0; j < QDIO_MAX_BUFFERS_PER_Q; ++j) {
			WARN_ON(card->qdio.out_qs[i]->bufs[j] != NULL);
			if (qeth_init_qdio_out_buf(card->qdio.out_qs[i], j))
				goto out_freeoutqbufs;
		}
	}

	/* completion */
	if (qeth_alloc_cq(card))
		goto out_freeoutq;

	return 0;

out_freeoutqbufs:
	while (j > 0) {
		--j;
		kmem_cache_free(qeth_qdio_outbuf_cache,
				card->qdio.out_qs[i]->bufs[j]);
		card->qdio.out_qs[i]->bufs[j] = NULL;
	}
out_freeoutq:
	while (i > 0)
		qeth_free_output_queue(card->qdio.out_qs[--i]);
	kfree(card->qdio.out_qs);
	card->qdio.out_qs = NULL;
out_freepool:
	qeth_free_buffer_pool(card);
out_freeinq:
	qeth_free_qdio_queue(card->qdio.in_q);
	card->qdio.in_q = NULL;
out_nomem:
	atomic_set(&card->qdio.state, QETH_QDIO_UNINITIALIZED);
	return -ENOMEM;
}