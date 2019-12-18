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
struct tep_handle {struct tep_function_handler* func_handlers; } ;
struct tep_function_handler {struct tep_function_handler* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_func_handle (struct tep_function_handler*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void remove_func_handler(struct tep_handle *tep, char *func_name)
{
	struct tep_function_handler *func;
	struct tep_function_handler **next;

	next = &tep->func_handlers;
	while ((func = *next)) {
		if (strcmp(func->name, func_name) == 0) {
			*next = func->next;
			free_func_handle(func);
			break;
		}
		next = &func->next;
	}
}