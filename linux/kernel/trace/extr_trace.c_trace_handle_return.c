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
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int TRACE_TYPE_HANDLED ; 
 int TRACE_TYPE_PARTIAL_LINE ; 
 scalar_t__ trace_seq_has_overflowed (struct trace_seq*) ; 

enum print_line_t trace_handle_return(struct trace_seq *s)
{
	return trace_seq_has_overflowed(s) ?
		TRACE_TYPE_PARTIAL_LINE : TRACE_TYPE_HANDLED;
}