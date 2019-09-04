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
struct trace_seq {scalar_t__ readpos; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_SEQ_CHECK (struct trace_seq*) ; 

void trace_seq_reset(struct trace_seq *s)
{
	if (!s)
		return;
	TRACE_SEQ_CHECK(s);
	s->len = 0;
	s->readpos = 0;
}