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
struct trace_seq {int /*<<< orphan*/  state; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  buffer_size; scalar_t__ readpos; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_SEQ_BUF_SIZE ; 
 int /*<<< orphan*/  TRACE_SEQ__GOOD ; 
 int /*<<< orphan*/  TRACE_SEQ__MEM_ALLOC_FAILED ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 

void trace_seq_init(struct trace_seq *s)
{
	s->len = 0;
	s->readpos = 0;
	s->buffer_size = TRACE_SEQ_BUF_SIZE;
	s->buffer = malloc(s->buffer_size);
	if (s->buffer != NULL)
		s->state = TRACE_SEQ__GOOD;
	else
		s->state = TRACE_SEQ__MEM_ALLOC_FAILED;
}