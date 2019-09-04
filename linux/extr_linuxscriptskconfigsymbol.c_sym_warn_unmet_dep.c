#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  expr; } ;
struct TYPE_4__ {scalar_t__ tri; int /*<<< orphan*/  expr; } ;
struct symbol {TYPE_1__ rev_dep; TYPE_2__ dir_dep; int /*<<< orphan*/  name; } ;
struct gstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  expr_gstr_print (int /*<<< orphan*/ ,struct gstr*) ; 
 int /*<<< orphan*/  expr_gstr_print_revdep (int /*<<< orphan*/ ,struct gstr*,scalar_t__,char*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mod ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  str_get (struct gstr*) ; 
 struct gstr str_new () ; 
 int /*<<< orphan*/  str_printf (struct gstr*,char*,...) ; 
 scalar_t__ yes ; 

__attribute__((used)) static void sym_warn_unmet_dep(struct symbol *sym)
{
	struct gstr gs = str_new();

	str_printf(&gs,
		   "\nWARNING: unmet direct dependencies detected for %s\n",
		   sym->name);
	str_printf(&gs,
		   "  Depends on [%c]: ",
		   sym->dir_dep.tri == mod ? 'm' : 'n');
	expr_gstr_print(sym->dir_dep.expr, &gs);
	str_printf(&gs, "\n");

	expr_gstr_print_revdep(sym->rev_dep.expr, &gs, yes,
			       "  Selected by [y]:\n");
	expr_gstr_print_revdep(sym->rev_dep.expr, &gs, mod,
			       "  Selected by [m]:\n");

	fputs(str_get(&gs), stderr);
}