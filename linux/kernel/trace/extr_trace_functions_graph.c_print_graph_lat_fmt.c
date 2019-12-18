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
struct trace_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_print_lat_fmt (struct trace_seq*,struct trace_entry*) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,char) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char*) ; 

__attribute__((used)) static void print_graph_lat_fmt(struct trace_seq *s, struct trace_entry *entry)
{
	trace_seq_putc(s, ' ');
	trace_print_lat_fmt(s, entry);
	trace_seq_puts(s, " | ");
}