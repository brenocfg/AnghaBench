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
struct trace_array_cpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct trace_array {TYPE_1__ trace_buffer; } ;
struct mmiotrace_rw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __trace_mmiotrace_rw (struct trace_array*,struct trace_array_cpu*,struct mmiotrace_rw*) ; 
 struct trace_array* mmio_trace_array ; 
 struct trace_array_cpu* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void mmio_trace_rw(struct mmiotrace_rw *rw)
{
	struct trace_array *tr = mmio_trace_array;
	struct trace_array_cpu *data = per_cpu_ptr(tr->trace_buffer.data, smp_processor_id());
	__trace_mmiotrace_rw(tr, data, rw);
}