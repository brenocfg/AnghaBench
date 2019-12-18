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
struct symsearch {scalar_t__ licence; int /*<<< orphan*/ * start; int /*<<< orphan*/  crcs; scalar_t__ unused; } ;
struct module {int dummy; } ;
struct find_symbol_arg {int /*<<< orphan*/ * sym; int /*<<< orphan*/  crc; struct module* owner; int /*<<< orphan*/  name; scalar_t__ warn; int /*<<< orphan*/  gplok; } ;

/* Variables and functions */
 scalar_t__ GPL_ONLY ; 
 scalar_t__ WILL_BE_GPL_ONLY ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  symversion (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static bool check_exported_symbol(const struct symsearch *syms,
				  struct module *owner,
				  unsigned int symnum, void *data)
{
	struct find_symbol_arg *fsa = data;

	if (!fsa->gplok) {
		if (syms->licence == GPL_ONLY)
			return false;
		if (syms->licence == WILL_BE_GPL_ONLY && fsa->warn) {
			pr_warn("Symbol %s is being used by a non-GPL module, "
				"which will not be allowed in the future\n",
				fsa->name);
		}
	}

#ifdef CONFIG_UNUSED_SYMBOLS
	if (syms->unused && fsa->warn) {
		pr_warn("Symbol %s is marked as UNUSED, however this module is "
			"using it.\n", fsa->name);
		pr_warn("This symbol will go away in the future.\n");
		pr_warn("Please evaluate if this is the right api to use and "
			"if it really is, submit a report to the linux kernel "
			"mailing list together with submitting your code for "
			"inclusion.\n");
	}
#endif

	fsa->owner = owner;
	fsa->crc = symversion(syms->crcs, symnum);
	fsa->sym = &syms->start[symnum];
	return true;
}