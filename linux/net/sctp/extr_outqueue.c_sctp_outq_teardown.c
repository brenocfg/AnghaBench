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
struct sctp_outq {int /*<<< orphan*/  asoc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sctp_outq_teardown (struct sctp_outq*) ; 
 int /*<<< orphan*/  sctp_outq_init (int /*<<< orphan*/ ,struct sctp_outq*) ; 

void sctp_outq_teardown(struct sctp_outq *q)
{
	__sctp_outq_teardown(q);
	sctp_outq_init(q->asoc, q);
}