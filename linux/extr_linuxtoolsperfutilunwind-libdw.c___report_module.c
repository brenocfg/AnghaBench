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
typedef  int /*<<< orphan*/  u64 ;
struct unwind_info {int /*<<< orphan*/  dwfl; int /*<<< orphan*/  thread; } ;
struct dso {scalar_t__ long_name; scalar_t__ symsrc_filename; int /*<<< orphan*/  short_name; } ;
struct addr_location {TYPE_1__* map; } ;
struct TYPE_2__ {scalar_t__ start; scalar_t__ pgoff; struct dso* dso; } ;
typedef  int /*<<< orphan*/  Dwfl_Module ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_MISC_USER ; 
 int /*<<< orphan*/ * dwfl_addrmodule (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwfl_module_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dwfl_report_elf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__,int) ; 
 int /*<<< orphan*/  thread__find_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addr_location*) ; 

__attribute__((used)) static int __report_module(struct addr_location *al, u64 ip,
			    struct unwind_info *ui)
{
	Dwfl_Module *mod;
	struct dso *dso = NULL;
	/*
	 * Some callers will use al->sym, so we can't just use the
	 * cheaper thread__find_map() here.
	 */
	thread__find_symbol(ui->thread, PERF_RECORD_MISC_USER, ip, al);

	if (al->map)
		dso = al->map->dso;

	if (!dso)
		return 0;

	mod = dwfl_addrmodule(ui->dwfl, ip);
	if (mod) {
		Dwarf_Addr s;

		dwfl_module_info(mod, NULL, &s, NULL, NULL, NULL, NULL, NULL);
		if (s != al->map->start - al->map->pgoff)
			mod = 0;
	}

	if (!mod)
		mod = dwfl_report_elf(ui->dwfl, dso->short_name,
				      (dso->symsrc_filename ? dso->symsrc_filename : dso->long_name), -1, al->map->start - al->map->pgoff,
				      false);

	return mod && dwfl_addrmodule(ui->dwfl, ip) == mod ? 0 : -1;
}