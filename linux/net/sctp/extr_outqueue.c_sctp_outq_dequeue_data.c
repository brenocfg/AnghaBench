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
struct sctp_outq {TYPE_1__* sched; } ;
struct sctp_chunk {int dummy; } ;
struct TYPE_2__ {struct sctp_chunk* (* dequeue ) (struct sctp_outq*) ;} ;

/* Variables and functions */
 struct sctp_chunk* stub1 (struct sctp_outq*) ; 

__attribute__((used)) static inline struct sctp_chunk *sctp_outq_dequeue_data(struct sctp_outq *q)
{
	return q->sched->dequeue(q);
}