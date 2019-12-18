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
struct trace_seq {int full; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int TRACE_SEQ_BUF_LEFT (struct trace_seq*) ; 
 int /*<<< orphan*/  __trace_seq_init (struct trace_seq*) ; 
 int /*<<< orphan*/  seq_buf_putc (int /*<<< orphan*/ *,unsigned char) ; 

void trace_seq_putc(struct trace_seq *s, unsigned char c)
{
	if (s->full)
		return;

	__trace_seq_init(s);

	if (TRACE_SEQ_BUF_LEFT(s) < 1) {
		s->full = 1;
		return;
	}

	seq_buf_putc(&s->seq, c);
}