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
struct trace_iterator {int dummy; } ;
struct trace_event {int dummy; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int trace_ctxwake_print (struct trace_iterator*,char*) ; 

__attribute__((used)) static enum print_line_t trace_ctx_print(struct trace_iterator *iter, int flags,
					 struct trace_event *event)
{
	return trace_ctxwake_print(iter, "==>");
}