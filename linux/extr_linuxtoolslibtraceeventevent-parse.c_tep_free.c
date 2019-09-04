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
struct tep_handle {int cmdline_count; int nr_events; struct tep_handle* func_resolver; struct tep_handle* sort_events; struct tep_handle* events; struct tep_handle* trace_clock; struct event_handler* handlers; struct tep_handle* printk; struct tep_handle* next; struct tep_handle* printk_map; scalar_t__ printk_count; struct tep_function_handler* func_handlers; struct tep_handle* mod; struct tep_handle* func; struct tep_handle* func_map; scalar_t__ func_count; struct tep_handle* comm; struct tep_handle* cmdlines; scalar_t__ ref_count; struct tep_handle* printklist; struct tep_handle* funclist; struct tep_handle* cmdlist; } ;
struct tep_function_handler {struct tep_function_handler* next; } ;
struct printk_list {int cmdline_count; int nr_events; struct printk_list* func_resolver; struct printk_list* sort_events; struct printk_list* events; struct printk_list* trace_clock; struct event_handler* handlers; struct printk_list* printk; struct printk_list* next; struct printk_list* printk_map; scalar_t__ printk_count; struct tep_function_handler* func_handlers; struct printk_list* mod; struct printk_list* func; struct printk_list* func_map; scalar_t__ func_count; struct printk_list* comm; struct printk_list* cmdlines; scalar_t__ ref_count; struct printk_list* printklist; struct printk_list* funclist; struct printk_list* cmdlist; } ;
struct func_list {int cmdline_count; int nr_events; struct func_list* func_resolver; struct func_list* sort_events; struct func_list* events; struct func_list* trace_clock; struct event_handler* handlers; struct func_list* printk; struct func_list* next; struct func_list* printk_map; scalar_t__ printk_count; struct tep_function_handler* func_handlers; struct func_list* mod; struct func_list* func; struct func_list* func_map; scalar_t__ func_count; struct func_list* comm; struct func_list* cmdlines; scalar_t__ ref_count; struct func_list* printklist; struct func_list* funclist; struct func_list* cmdlist; } ;
struct event_handler {struct event_handler* next; } ;
struct cmdline_list {int cmdline_count; int nr_events; struct cmdline_list* func_resolver; struct cmdline_list* sort_events; struct cmdline_list* events; struct cmdline_list* trace_clock; struct event_handler* handlers; struct cmdline_list* printk; struct cmdline_list* next; struct cmdline_list* printk_map; scalar_t__ printk_count; struct tep_function_handler* func_handlers; struct cmdline_list* mod; struct cmdline_list* func; struct cmdline_list* func_map; scalar_t__ func_count; struct cmdline_list* comm; struct cmdline_list* cmdlines; scalar_t__ ref_count; struct cmdline_list* printklist; struct cmdline_list* funclist; struct cmdline_list* cmdlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tep_handle*) ; 
 int /*<<< orphan*/  free_func_handle (struct tep_function_handler*) ; 
 int /*<<< orphan*/  free_handler (struct event_handler*) ; 
 int /*<<< orphan*/  tep_free_format (struct tep_handle) ; 

void tep_free(struct tep_handle *pevent)
{
	struct cmdline_list *cmdlist, *cmdnext;
	struct func_list *funclist, *funcnext;
	struct printk_list *printklist, *printknext;
	struct tep_function_handler *func_handler;
	struct event_handler *handle;
	int i;

	if (!pevent)
		return;

	cmdlist = pevent->cmdlist;
	funclist = pevent->funclist;
	printklist = pevent->printklist;

	pevent->ref_count--;
	if (pevent->ref_count)
		return;

	if (pevent->cmdlines) {
		for (i = 0; i < pevent->cmdline_count; i++)
			free(pevent->cmdlines[i].comm);
		free(pevent->cmdlines);
	}

	while (cmdlist) {
		cmdnext = cmdlist->next;
		free(cmdlist->comm);
		free(cmdlist);
		cmdlist = cmdnext;
	}

	if (pevent->func_map) {
		for (i = 0; i < (int)pevent->func_count; i++) {
			free(pevent->func_map[i].func);
			free(pevent->func_map[i].mod);
		}
		free(pevent->func_map);
	}

	while (funclist) {
		funcnext = funclist->next;
		free(funclist->func);
		free(funclist->mod);
		free(funclist);
		funclist = funcnext;
	}

	while (pevent->func_handlers) {
		func_handler = pevent->func_handlers;
		pevent->func_handlers = func_handler->next;
		free_func_handle(func_handler);
	}

	if (pevent->printk_map) {
		for (i = 0; i < (int)pevent->printk_count; i++)
			free(pevent->printk_map[i].printk);
		free(pevent->printk_map);
	}

	while (printklist) {
		printknext = printklist->next;
		free(printklist->printk);
		free(printklist);
		printklist = printknext;
	}

	for (i = 0; i < pevent->nr_events; i++)
		tep_free_format(pevent->events[i]);

	while (pevent->handlers) {
		handle = pevent->handlers;
		pevent->handlers = handle->next;
		free_handler(handle);
	}

	free(pevent->trace_clock);
	free(pevent->events);
	free(pevent->sort_events);
	free(pevent->func_resolver);

	free(pevent);
}