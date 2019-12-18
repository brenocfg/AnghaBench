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
struct sctp_outq {scalar_t__ cork; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_outq_flush (struct sctp_outq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sctp_outq_uncork(struct sctp_outq *q, gfp_t gfp)
{
	if (q->cork)
		q->cork = 0;

	sctp_outq_flush(q, 0, gfp);
}