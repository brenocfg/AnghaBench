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
struct exception_handler_data {int /*<<< orphan*/  dbghelp; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_DBGHELP_IMPORT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LoadLibraryW (char*) ; 
 int /*<<< orphan*/  enumerate_loaded_modules64 ; 
 int /*<<< orphan*/  minidump_write_dump ; 
 int /*<<< orphan*/  stack_walk64 ; 
 int /*<<< orphan*/  sym_cleanup ; 
 int /*<<< orphan*/  sym_from_addr ; 
 int /*<<< orphan*/  sym_function_table_access64 ; 
 int /*<<< orphan*/  sym_get_module_base64 ; 
 int /*<<< orphan*/  sym_get_module_info64 ; 
 int /*<<< orphan*/  sym_initialize ; 
 int /*<<< orphan*/  sym_refresh_module_list ; 
 int /*<<< orphan*/  sym_set_options ; 

__attribute__((used)) static inline bool get_dbghelp_imports(struct exception_handler_data *data)
{
	data->dbghelp = LoadLibraryW(L"DbgHelp");
	if (!data->dbghelp)
		return false;

	GET_DBGHELP_IMPORT(sym_initialize, "SymInitialize");
	GET_DBGHELP_IMPORT(sym_cleanup, "SymCleanup");
	GET_DBGHELP_IMPORT(sym_set_options, "SymSetOptions");
	GET_DBGHELP_IMPORT(sym_function_table_access64,
			   "SymFunctionTableAccess64");
	GET_DBGHELP_IMPORT(sym_get_module_base64, "SymGetModuleBase64");
	GET_DBGHELP_IMPORT(sym_from_addr, "SymFromAddrW");
	GET_DBGHELP_IMPORT(sym_get_module_info64, "SymGetModuleInfo64");
	GET_DBGHELP_IMPORT(sym_refresh_module_list, "SymRefreshModuleList");
	GET_DBGHELP_IMPORT(stack_walk64, "StackWalk64");
	GET_DBGHELP_IMPORT(enumerate_loaded_modules64,
			   "EnumerateLoadedModulesW64");
	GET_DBGHELP_IMPORT(minidump_write_dump, "MiniDumpWriteDump");

	return true;
}