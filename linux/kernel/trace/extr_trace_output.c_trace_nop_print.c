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
struct trace_iterator {int /*<<< orphan*/  seq; TYPE_1__* ent; } ;
struct trace_event {int dummy; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int trace_handle_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_seq_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

enum print_line_t trace_nop_print(struct trace_iterator *iter, int flags,
				  struct trace_event *event)
{
	trace_seq_printf(&iter->seq, "type: %d\n", iter->ent->type);

	return trace_handle_return(&iter->seq);
}