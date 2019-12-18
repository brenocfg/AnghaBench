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
struct tep_plugin_list {struct tep_plugin_list* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,char const*,int /*<<< orphan*/ ,char const*) ; 

void tep_print_plugins(struct trace_seq *s,
		       const char *prefix, const char *suffix,
		       const struct tep_plugin_list *list)
{
	while (list) {
		trace_seq_printf(s, "%s%s%s", prefix, list->name, suffix);
		list = list->next;
	}
}