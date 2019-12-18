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
struct exception_handler_data {int /*<<< orphan*/  dbghelp; int /*<<< orphan*/  module_list; int /*<<< orphan*/  module_name; int /*<<< orphan*/  cpu_info; int /*<<< orphan*/  str; int /*<<< orphan*/  sym_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
exception_handler_data_free(struct exception_handler_data *data)
{
	LocalFree(data->sym_info);
	dstr_free(&data->str);
	dstr_free(&data->cpu_info);
	dstr_free(&data->module_name);
	dstr_free(&data->module_list);
	FreeLibrary(data->dbghelp);
}