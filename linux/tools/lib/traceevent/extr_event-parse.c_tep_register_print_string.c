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
struct tep_handle {int /*<<< orphan*/  printk_count; struct printk_list* printklist; } ;
struct printk_list {unsigned long long addr; char* printk; struct printk_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct printk_list*) ; 
 struct printk_list* malloc (int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 int strlen (char*) ; 

int tep_register_print_string(struct tep_handle *tep, const char *fmt,
			      unsigned long long addr)
{
	struct printk_list *item = malloc(sizeof(*item));
	char *p;

	if (!item)
		return -1;

	item->next = tep->printklist;
	item->addr = addr;

	/* Strip off quotes and '\n' from the end */
	if (fmt[0] == '"')
		fmt++;
	item->printk = strdup(fmt);
	if (!item->printk)
		goto out_free;

	p = item->printk + strlen(item->printk) - 1;
	if (*p == '"')
		*p = 0;

	p -= 2;
	if (strcmp(p, "\\n") == 0)
		*p = 0;

	tep->printklist = item;
	tep->printk_count++;

	return 0;

out_free:
	free(item);
	errno = ENOMEM;
	return -1;
}