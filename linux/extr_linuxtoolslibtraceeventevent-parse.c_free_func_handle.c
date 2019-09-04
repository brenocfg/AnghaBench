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
struct tep_function_handler {struct tep_function_handler* next; struct tep_function_handler* params; struct tep_function_handler* name; } ;
struct func_params {struct func_params* next; struct func_params* params; struct func_params* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tep_function_handler*) ; 

__attribute__((used)) static void free_func_handle(struct tep_function_handler *func)
{
	struct func_params *params;

	free(func->name);

	while (func->params) {
		params = func->params;
		func->params = params->next;
		free(params);
	}

	free(func);
}