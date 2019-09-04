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
typedef  scalar_t__ u64 ;
struct trace_array {scalar_t__ max_latency; } ;

/* Variables and functions */
 scalar_t__ tracing_thresh ; 

__attribute__((used)) static bool report_latency(struct trace_array *tr, u64 delta)
{
	if (tracing_thresh) {
		if (delta < tracing_thresh)
			return false;
	} else {
		if (delta <= tr->max_latency)
			return false;
	}
	return true;
}