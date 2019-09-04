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
typedef  void* libapi_print_fn_t ;

/* Variables and functions */
 void* __pr_debug ; 
 void* __pr_info ; 
 void* __pr_warning ; 

void libapi_set_print(libapi_print_fn_t warn,
		      libapi_print_fn_t info,
		      libapi_print_fn_t debug)
{
	__pr_warning = warn;
	__pr_info    = info;
	__pr_debug   = debug;
}