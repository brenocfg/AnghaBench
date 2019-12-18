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
struct var_list {int number; void* pointer; struct var_list* next; } ;

/* Variables and functions */
 struct var_list* ivlist ; 

void *
ECPGget_var(int number)
{
	struct var_list *ptr;

	for (ptr = ivlist; ptr != NULL && ptr->number != number; ptr = ptr->next);
	return (ptr) ? ptr->pointer : NULL;
}