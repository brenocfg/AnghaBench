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
struct trace_array {int dummy; } ;

/* Variables and functions */
 int hwlat_busy ; 
 int /*<<< orphan*/  last_tracing_thresh ; 
 int /*<<< orphan*/  save_tracing_thresh ; 
 int /*<<< orphan*/  stop_kthread () ; 
 int /*<<< orphan*/  tracing_thresh ; 

__attribute__((used)) static void hwlat_tracer_reset(struct trace_array *tr)
{
	stop_kthread();

	/* the tracing threshold is static between runs */
	last_tracing_thresh = tracing_thresh;

	tracing_thresh = save_tracing_thresh;
	hwlat_busy = false;
}