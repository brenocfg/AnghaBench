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
struct dialog_list {struct dialog_list* next; } ;

/* Variables and functions */
 struct dialog_list* item_head ; 

int item_count(void)
{
	int n = 0;
	struct dialog_list *p;

	for (p = item_head; p; p = p->next)
		n++;
	return n;
}