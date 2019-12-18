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
struct sctp_outq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sctp_outq_teardown (struct sctp_outq*) ; 

void sctp_outq_free(struct sctp_outq *q)
{
	/* Throw away leftover chunks. */
	__sctp_outq_teardown(q);
}