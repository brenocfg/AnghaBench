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
struct sctp_outq {scalar_t__ out_qlen; scalar_t__ outstanding_bytes; int /*<<< orphan*/  retransmit; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

int sctp_outq_is_empty(const struct sctp_outq *q)
{
	return q->out_qlen == 0 && q->outstanding_bytes == 0 &&
	       list_empty(&q->retransmit);
}