#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ readpos; } ;
struct trace_seq {scalar_t__ buffer; TYPE_1__ seq; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EBUSY ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,size_t) ; 
 scalar_t__ trace_seq_used (struct trace_seq*) ; 

__attribute__((used)) static ssize_t trace_seq_to_buffer(struct trace_seq *s, void *buf, size_t cnt)
{
	int len;

	if (trace_seq_used(s) <= s->seq.readpos)
		return -EBUSY;

	len = trace_seq_used(s) - s->seq.readpos;
	if (cnt > len)
		cnt = len;
	memcpy(buf, s->buffer + s->seq.readpos, cnt);

	s->seq.readpos += cnt;
	return cnt;
}