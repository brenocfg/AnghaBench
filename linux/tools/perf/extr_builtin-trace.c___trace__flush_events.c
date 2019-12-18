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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ last; int /*<<< orphan*/  data; } ;
struct trace {TYPE_1__ oe; } ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 scalar_t__ ordered_events__first_time (int /*<<< orphan*/ *) ; 
 int ordered_events__flush_time (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int __trace__flush_events(struct trace *trace)
{
	u64 first = ordered_events__first_time(&trace->oe.data);
	u64 flush = trace->oe.last - NSEC_PER_SEC;

	/* Is there some thing to flush.. */
	if (first && first < flush)
		return ordered_events__flush_time(&trace->oe.data, flush);

	return 0;
}