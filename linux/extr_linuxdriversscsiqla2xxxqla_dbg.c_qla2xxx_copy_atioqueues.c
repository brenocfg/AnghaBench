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
typedef  int uint32_t ;
struct TYPE_2__ {void* atio_ring; int atio_q_length; } ;
struct qla_hw_data {TYPE_1__ tgt; } ;
struct qla2xxx_mqueue_header {void* size; void* number; void* queue; } ;
struct qla2xxx_mqueue_chain {int type; void* chain_size; } ;
typedef  int /*<<< orphan*/  request_t ;

/* Variables and functions */
 int DUMP_CHAIN_QUEUE ; 
 int TYPE_ATIO_QUEUE ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static inline void *
qla2xxx_copy_atioqueues(struct qla_hw_data *ha, void *ptr,
	uint32_t **last_chain)
{
	struct qla2xxx_mqueue_chain *q;
	struct qla2xxx_mqueue_header *qh;
	uint32_t num_queues;
	int que;
	struct {
		int length;
		void *ring;
	} aq, *aqp;

	if (!ha->tgt.atio_ring)
		return ptr;

	num_queues = 1;
	aqp = &aq;
	aqp->length = ha->tgt.atio_q_length;
	aqp->ring = ha->tgt.atio_ring;

	for (que = 0; que < num_queues; que++) {
		/* aqp = ha->atio_q_map[que]; */
		q = ptr;
		*last_chain = &q->type;
		q->type = htonl(DUMP_CHAIN_QUEUE);
		q->chain_size = htonl(
		    sizeof(struct qla2xxx_mqueue_chain) +
		    sizeof(struct qla2xxx_mqueue_header) +
		    (aqp->length * sizeof(request_t)));
		ptr += sizeof(struct qla2xxx_mqueue_chain);

		/* Add header. */
		qh = ptr;
		qh->queue = htonl(TYPE_ATIO_QUEUE);
		qh->number = htonl(que);
		qh->size = htonl(aqp->length * sizeof(request_t));
		ptr += sizeof(struct qla2xxx_mqueue_header);

		/* Add data. */
		memcpy(ptr, aqp->ring, aqp->length * sizeof(request_t));

		ptr += aqp->length * sizeof(request_t);
	}

	return ptr;
}