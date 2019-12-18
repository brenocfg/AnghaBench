#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct probe_trace_point {unsigned long offset; unsigned long address; int retprobe; int /*<<< orphan*/  symbol; } ;
struct TYPE_3__ {scalar_t__ st_value; } ;
typedef  TYPE_1__ GElf_Sym ;
typedef  int /*<<< orphan*/  Dwfl_Module ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 char* dwarf_diename (int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_entrypc (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ dwarf_highpc (int /*<<< orphan*/ *,scalar_t__*) ; 
 char* dwfl_module_addrsym (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static int convert_to_trace_point(Dwarf_Die *sp_die, Dwfl_Module *mod,
				  Dwarf_Addr paddr, bool retprobe,
				  const char *function,
				  struct probe_trace_point *tp)
{
	Dwarf_Addr eaddr, highaddr;
	GElf_Sym sym;
	const char *symbol;

	/* Verify the address is correct */
	if (dwarf_entrypc(sp_die, &eaddr) != 0) {
		pr_warning("Failed to get entry address of %s\n",
			   dwarf_diename(sp_die));
		return -ENOENT;
	}
	if (dwarf_highpc(sp_die, &highaddr) != 0) {
		pr_warning("Failed to get end address of %s\n",
			   dwarf_diename(sp_die));
		return -ENOENT;
	}
	if (paddr > highaddr) {
		pr_warning("Offset specified is greater than size of %s\n",
			   dwarf_diename(sp_die));
		return -EINVAL;
	}

	symbol = dwarf_diename(sp_die);
	if (!symbol) {
		/* Try to get the symbol name from symtab */
		symbol = dwfl_module_addrsym(mod, paddr, &sym, NULL);
		if (!symbol) {
			pr_warning("Failed to find symbol at 0x%lx\n",
				   (unsigned long)paddr);
			return -ENOENT;
		}
		eaddr = sym.st_value;
	}
	tp->offset = (unsigned long)(paddr - eaddr);
	tp->address = (unsigned long)paddr;
	tp->symbol = strdup(symbol);
	if (!tp->symbol)
		return -ENOMEM;

	/* Return probe must be on the head of a subprogram */
	if (retprobe) {
		if (eaddr != paddr) {
			pr_warning("Failed to find \"%s%%return\",\n"
				   " because %s is an inlined function and"
				   " has no return point.\n", function,
				   function);
			return -EINVAL;
		}
		tp->retprobe = true;
	}

	return 0;
}