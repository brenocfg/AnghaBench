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
struct trace_iterator {TYPE_1__* trace_buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 unsigned long atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dropped_count ; 
 unsigned long prev_overruns ; 
 unsigned long ring_buffer_overruns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long count_overruns(struct trace_iterator *iter)
{
	unsigned long cnt = atomic_xchg(&dropped_count, 0);
	unsigned long over = ring_buffer_overruns(iter->trace_buffer->buffer);

	if (over > prev_overruns)
		cnt += over - prev_overruns;
	prev_overruns = over;
	return cnt;
}