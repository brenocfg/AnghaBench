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
struct trace_array {scalar_t__ max_latency; } ;
struct TYPE_2__ {scalar_t__ count; } ;

/* Variables and functions */
 int EBUSY ; 
 int disable_migrate ; 
 int hwlat_busy ; 
 TYPE_1__ hwlat_data ; 
 struct trace_array* hwlat_trace ; 
 int /*<<< orphan*/  hwlat_tracer_start (struct trace_array*) ; 
 scalar_t__ last_tracing_thresh ; 
 scalar_t__ save_tracing_thresh ; 
 scalar_t__ tracer_tracing_is_on (struct trace_array*) ; 
 scalar_t__ tracing_thresh ; 

__attribute__((used)) static int hwlat_tracer_init(struct trace_array *tr)
{
	/* Only allow one instance to enable this */
	if (hwlat_busy)
		return -EBUSY;

	hwlat_trace = tr;

	disable_migrate = false;
	hwlat_data.count = 0;
	tr->max_latency = 0;
	save_tracing_thresh = tracing_thresh;

	/* tracing_thresh is in nsecs, we speak in usecs */
	if (!tracing_thresh)
		tracing_thresh = last_tracing_thresh;

	if (tracer_tracing_is_on(tr))
		hwlat_tracer_start(tr);

	hwlat_busy = true;

	return 0;
}