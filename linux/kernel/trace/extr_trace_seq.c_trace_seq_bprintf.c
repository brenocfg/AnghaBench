#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {unsigned int len; } ;
struct trace_seq {int full; TYPE_1__ seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __trace_seq_init (struct trace_seq*) ; 
 int /*<<< orphan*/  seq_buf_bprintf (TYPE_1__*,char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  seq_buf_has_overflowed (TYPE_1__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void trace_seq_bprintf(struct trace_seq *s, const char *fmt, const u32 *binary)
{
	unsigned int save_len = s->seq.len;

	if (s->full)
		return;

	__trace_seq_init(s);

	seq_buf_bprintf(&s->seq, fmt, binary);

	/* If we can't write it all, don't bother writing anything */
	if (unlikely(seq_buf_has_overflowed(&s->seq))) {
		s->seq.len = save_len;
		s->full = 1;
		return;
	}
}