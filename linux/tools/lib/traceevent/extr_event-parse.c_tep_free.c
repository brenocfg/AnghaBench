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
struct tep_handle {int cmdline_count; int nr_events; struct tep_handle* func_resolver; struct tep_handle* sort_events; struct tep_handle* events; struct event_handler* handlers; struct tep_handle* printk; struct tep_handle* next; struct tep_handle* printk_map; scalar_t__ printk_count; struct tep_function_handler* func_handlers; struct tep_handle* mod; struct tep_handle* func; struct tep_handle* func_map; scalar_t__ func_count; struct tep_handle* comm; struct tep_handle* cmdlines; scalar_t__ ref_count; struct tep_handle* printklist; struct tep_handle* funclist; struct tep_handle* cmdlist; } ;
struct tep_function_handler {struct tep_function_handler* next; } ;
struct printk_list {int cmdline_count; int nr_events; struct printk_list* func_resolver; struct printk_list* sort_events; struct printk_list* events; struct event_handler* handlers; struct printk_list* printk; struct printk_list* next; struct printk_list* printk_map; scalar_t__ printk_count; struct tep_function_handler* func_handlers; struct printk_list* mod; struct printk_list* func; struct printk_list* func_map; scalar_t__ func_count; struct printk_list* comm; struct printk_list* cmdlines; scalar_t__ ref_count; struct printk_list* printklist; struct printk_list* funclist; struct printk_list* cmdlist; } ;
struct func_list {int cmdline_count; int nr_events; struct func_list* func_resolver; struct func_list* sort_events; struct func_list* events; struct event_handler* handlers; struct func_list* printk; struct func_list* next; struct func_list* printk_map; scalar_t__ printk_count; struct tep_function_handler* func_handlers; struct func_list* mod; struct func_list* func; struct func_list* func_map; scalar_t__ func_count; struct func_list* comm; struct func_list* cmdlines; scalar_t__ ref_count; struct func_list* printklist; struct func_list* funclist; struct func_list* cmdlist; } ;
struct event_handler {struct event_handler* next; } ;
struct cmdline_list {int cmdline_count; int nr_events; struct cmdline_list* func_resolver; struct cmdline_list* sort_events; struct cmdline_list* events; struct event_handler* handlers; struct cmdline_list* printk; struct cmdline_list* next; struct cmdline_list* printk_map; scalar_t__ printk_count; struct tep_function_handler* func_handlers; struct cmdline_list* mod; struct cmdline_list* func; struct cmdline_list* func_map; scalar_t__ func_count; struct cmdline_list* comm; struct cmdline_list* cmdlines; scalar_t__ ref_count; struct cmdline_list* printklist; struct cmdline_list* funclist; struct cmdline_list* cmdlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tep_handle*) ; 
 int /*<<< orphan*/  free_func_handle (struct tep_function_handler*) ; 
 int /*<<< orphan*/  free_handler (struct event_handler*) ; 
 int /*<<< orphan*/  tep_free_event (struct tep_handle) ; 

void tep_free(struct tep_handle *tep)
{
	struct cmdline_list *cmdlist, *cmdnext;
	struct func_list *funclist, *funcnext;
	struct printk_list *printklist, *printknext;
	struct tep_function_handler *func_handler;
	struct event_handler *handle;
	int i;

	if (!tep)
		return;

	cmdlist = tep->cmdlist;
	funclist = tep->funclist;
	printklist = tep->printklist;

	tep->ref_count--;
	if (tep->ref_count)
		return;

	if (tep->cmdlines) {
		for (i = 0; i < tep->cmdline_count; i++)
			free(tep->cmdlines[i].comm);
		free(tep->cmdlines);
	}

	while (cmdlist) {
		cmdnext = cmdlist->next;
		free(cmdlist->comm);
		free(cmdlist);
		cmdlist = cmdnext;
	}

	if (tep->func_map) {
		for (i = 0; i < (int)tep->func_count; i++) {
			free(tep->func_map[i].func);
			free(tep->func_map[i].mod);
		}
		free(tep->func_map);
	}

	while (funclist) {
		funcnext = funclist->next;
		free(funclist->func);
		free(funclist->mod);
		free(funclist);
		funclist = funcnext;
	}

	while (tep->func_handlers) {
		func_handler = tep->func_handlers;
		tep->func_handlers = func_handler->next;
		free_func_handle(func_handler);
	}

	if (tep->printk_map) {
		for (i = 0; i < (int)tep->printk_count; i++)
			free(tep->printk_map[i].printk);
		free(tep->printk_map);
	}

	while (printklist) {
		printknext = printklist->next;
		free(printklist->printk);
		free(printklist);
		printklist = printknext;
	}

	for (i = 0; i < tep->nr_events; i++)
		tep_free_event(tep->events[i]);

	while (tep->handlers) {
		handle = tep->handlers;
		tep->handlers = handle->next;
		free_handler(handle);
	}

	free(tep->events);
	free(tep->sort_events);
	free(tep->func_resolver);

	free(tep);
}