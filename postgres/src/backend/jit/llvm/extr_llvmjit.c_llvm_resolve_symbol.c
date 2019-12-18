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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (char*) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ LLVMSearchForAddressOfSymbol (char const*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  llvm_split_symbol_name (char const*,char**,char**) ; 
 scalar_t__ load_external_function (char*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static uint64_t
llvm_resolve_symbol(const char *symname, void *ctx)
{
	uintptr_t	addr;
	char	   *funcname;
	char	   *modname;

	/*
	 * macOS prefixes all object level symbols with an underscore. But neither
	 * dlsym() nor PG's inliner expect that. So undo.
	 */
#if defined(__darwin__)
	if (symname[0] != '_')
		elog(ERROR, "expected prefixed symbol name, but got \"%s\"", symname);
	symname++;
#endif

	llvm_split_symbol_name(symname, &modname, &funcname);

	/* functions that aren't resolved to names shouldn't ever get here */
	Assert(funcname);

	if (modname)
		addr = (uintptr_t) load_external_function(modname, funcname,
												  true, NULL);
	else
		addr = (uintptr_t) LLVMSearchForAddressOfSymbol(symname);

	pfree(funcname);
	if (modname)
		pfree(modname);

	/* let LLVM will error out - should never happen */
	if (!addr)
		elog(WARNING, "failed to resolve name %s", symname);

	return (uint64_t) addr;
}