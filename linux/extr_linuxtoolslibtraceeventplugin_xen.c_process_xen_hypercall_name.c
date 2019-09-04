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
struct trace_seq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_hypercall_name (unsigned int) ; 

unsigned long long process_xen_hypercall_name(struct trace_seq *s,
					      unsigned long long *args)
{
	unsigned int op = args[0];

	trace_seq_printf(s, "%s", xen_hypercall_name(op));
	return 0;
}