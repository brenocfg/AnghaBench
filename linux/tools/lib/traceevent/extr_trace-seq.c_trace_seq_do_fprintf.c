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
struct trace_seq {int state; char* len; int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_SEQ_CHECK (struct trace_seq*) ; 
#define  TRACE_SEQ__BUFFER_POISONED 130 
#define  TRACE_SEQ__GOOD 129 
#define  TRACE_SEQ__MEM_ALLOC_FAILED 128 
 int fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 

int trace_seq_do_fprintf(struct trace_seq *s, FILE *fp)
{
	TRACE_SEQ_CHECK(s);

	switch (s->state) {
	case TRACE_SEQ__GOOD:
		return fprintf(fp, "%.*s", s->len, s->buffer);
	case TRACE_SEQ__BUFFER_POISONED:
		fprintf(fp, "%s\n", "Usage of trace_seq after it was destroyed");
		break;
	case TRACE_SEQ__MEM_ALLOC_FAILED:
		fprintf(fp, "%s\n", "Can't allocate trace_seq buffer memory");
		break;
	}
	return -1;
}