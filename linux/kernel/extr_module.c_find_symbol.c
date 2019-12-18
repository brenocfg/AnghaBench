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
struct module {int dummy; } ;
struct kernel_symbol {int dummy; } ;
struct find_symbol_arg {char const* name; int gplok; int warn; struct kernel_symbol const* sym; int /*<<< orphan*/ * crc; struct module* owner; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ each_symbol_section (int /*<<< orphan*/ ,struct find_symbol_arg*) ; 
 int /*<<< orphan*/  find_exported_symbol_in_section ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 

const struct kernel_symbol *find_symbol(const char *name,
					struct module **owner,
					const s32 **crc,
					bool gplok,
					bool warn)
{
	struct find_symbol_arg fsa;

	fsa.name = name;
	fsa.gplok = gplok;
	fsa.warn = warn;

	if (each_symbol_section(find_exported_symbol_in_section, &fsa)) {
		if (owner)
			*owner = fsa.owner;
		if (crc)
			*crc = fsa.crc;
		return fsa.sym;
	}

	pr_debug("Failed to find symbol %s\n", name);
	return NULL;
}