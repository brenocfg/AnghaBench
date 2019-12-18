#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct exception_handler_data {TYPE_1__* sym_info; int /*<<< orphan*/  process; int /*<<< orphan*/  (* sym_refresh_module_list ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sym_initialize ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* sym_set_options ) (int) ;} ;
struct TYPE_2__ {int SizeOfStruct; int MaxNameLen; } ;
typedef  int /*<<< orphan*/  SYMBOL_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  LPTR ; 
 TYPE_1__* LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int SYMOPT_FAIL_CRITICAL_ERRORS ; 
 int SYMOPT_LOAD_ANYTHING ; 
 int SYMOPT_UNDNAME ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_initialize_called ; 

__attribute__((used)) static inline void init_sym_info(struct exception_handler_data *data)
{
	data->sym_set_options(SYMOPT_UNDNAME | SYMOPT_FAIL_CRITICAL_ERRORS |
			      SYMOPT_LOAD_ANYTHING);

	if (!sym_initialize_called)
		data->sym_initialize(data->process, NULL, true);
	else
		data->sym_refresh_module_list(data->process);

	data->sym_info = LocalAlloc(LPTR, sizeof(*data->sym_info) + 256);
	data->sym_info->SizeOfStruct = sizeof(SYMBOL_INFO);
	data->sym_info->MaxNameLen = 256;
}