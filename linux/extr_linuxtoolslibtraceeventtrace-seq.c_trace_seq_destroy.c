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
struct trace_seq {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_SEQ_CHECK_RET (struct trace_seq*) ; 
 int /*<<< orphan*/  TRACE_SEQ_POISON ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void trace_seq_destroy(struct trace_seq *s)
{
	if (!s)
		return;
	TRACE_SEQ_CHECK_RET(s);
	free(s->buffer);
	s->buffer = TRACE_SEQ_POISON;
}