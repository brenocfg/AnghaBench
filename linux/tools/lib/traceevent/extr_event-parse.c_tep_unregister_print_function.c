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
typedef  scalar_t__ tep_func_handler ;
struct tep_handle {int dummy; } ;
struct tep_function_handler {scalar_t__ func; } ;

/* Variables and functions */
 struct tep_function_handler* find_func_handler (struct tep_handle*,char*) ; 
 int /*<<< orphan*/  remove_func_handler (struct tep_handle*,char*) ; 

int tep_unregister_print_function(struct tep_handle *tep,
				  tep_func_handler func, char *name)
{
	struct tep_function_handler *func_handle;

	func_handle = find_func_handler(tep, name);
	if (func_handle && func_handle->func == func) {
		remove_func_handler(tep, name);
		return 0;
	}
	return -1;
}