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
struct trace_seq {char* buffer; scalar_t__ buffer_size; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ TRACE_SEQ_BUF_SIZE ; 
 int /*<<< orphan*/  TRACE_SEQ__MEM_ALLOC_FAILED ; 
 scalar_t__ WARN_ONCE (int,char*) ; 
 char* realloc (char*,scalar_t__) ; 

__attribute__((used)) static void expand_buffer(struct trace_seq *s)
{
	char *buf;

	buf = realloc(s->buffer, s->buffer_size + TRACE_SEQ_BUF_SIZE);
	if (WARN_ONCE(!buf, "Can't allocate trace_seq buffer memory")) {
		s->state = TRACE_SEQ__MEM_ALLOC_FAILED;
		return;
	}

	s->buffer = buf;
	s->buffer_size += TRACE_SEQ_BUF_SIZE;
}