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
struct tep_handle {int /*<<< orphan*/  func_count; struct func_list* funclist; } ;
struct func_list {unsigned long long addr; struct func_list* func; int /*<<< orphan*/ * mod; struct func_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct func_list*) ; 
 struct func_list* malloc (int) ; 
 void* strdup (char*) ; 

int tep_register_function(struct tep_handle *tep, char *func,
			  unsigned long long addr, char *mod)
{
	struct func_list *item = malloc(sizeof(*item));

	if (!item)
		return -1;

	item->next = tep->funclist;
	item->func = strdup(func);
	if (!item->func)
		goto out_free;

	if (mod) {
		item->mod = strdup(mod);
		if (!item->mod)
			goto out_free_func;
	} else
		item->mod = NULL;
	item->addr = addr;

	tep->funclist = item;
	tep->func_count++;

	return 0;

out_free_func:
	free(item->func);
	item->func = NULL;
out_free:
	free(item);
	errno = ENOMEM;
	return -1;
}