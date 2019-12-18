#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trace_seq {int dummy; } ;
struct trace_iterator {int iter_flags; int idx; int /*<<< orphan*/  cpu; int /*<<< orphan*/  started; TYPE_1__* trace_buffer; struct trace_array* tr; struct trace_seq seq; } ;
struct trace_array {int trace_flags; } ;
struct TYPE_4__ {scalar_t__ skipped_entries; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int TRACE_FILE_ANNOTATE ; 
 int TRACE_ITER_ANNOTATE ; 
 scalar_t__ cpumask_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_test_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_cpu_buff_start(struct trace_iterator *iter)
{
	struct trace_seq *s = &iter->seq;
	struct trace_array *tr = iter->tr;

	if (!(tr->trace_flags & TRACE_ITER_ANNOTATE))
		return;

	if (!(iter->iter_flags & TRACE_FILE_ANNOTATE))
		return;

	if (cpumask_available(iter->started) &&
	    cpumask_test_cpu(iter->cpu, iter->started))
		return;

	if (per_cpu_ptr(iter->trace_buffer->data, iter->cpu)->skipped_entries)
		return;

	if (cpumask_available(iter->started))
		cpumask_set_cpu(iter->cpu, iter->started);

	/* Don't print started cpu buffer for the first entry of the trace */
	if (iter->idx > 1)
		trace_seq_printf(s, "##### CPU %u buffer started ####\n",
				iter->cpu);
}