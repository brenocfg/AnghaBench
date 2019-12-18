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
typedef  int /*<<< orphan*/  uintmax_t ;
struct probe_finder {scalar_t__ addr; TYPE_1__* pev; } ;
struct perf_probe_point {scalar_t__ offset; scalar_t__ lazy_line; } ;
struct TYPE_2__ {struct perf_probe_point point; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 int ENOENT ; 
 int call_probe_finder (int /*<<< orphan*/ *,struct probe_finder*) ; 
 int /*<<< orphan*/  dwarf_diename (int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_entrypc (int /*<<< orphan*/ *,scalar_t__*) ; 
 int find_probe_point_lazy (int /*<<< orphan*/ *,struct probe_finder*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int probe_point_inline_cb(Dwarf_Die *in_die, void *data)
{
	struct probe_finder *pf = data;
	struct perf_probe_point *pp = &pf->pev->point;
	Dwarf_Addr addr;
	int ret;

	if (pp->lazy_line)
		ret = find_probe_point_lazy(in_die, pf);
	else {
		/* Get probe address */
		if (dwarf_entrypc(in_die, &addr) != 0) {
			pr_warning("Failed to get entry address of %s.\n",
				   dwarf_diename(in_die));
			return -ENOENT;
		}
		if (addr == 0) {
			pr_debug("%s has no valid entry address. skipped.\n",
				 dwarf_diename(in_die));
			return -ENOENT;
		}
		pf->addr = addr;
		pf->addr += pp->offset;
		pr_debug("found inline addr: 0x%jx\n",
			 (uintmax_t)pf->addr);

		ret = call_probe_finder(in_die, pf);
	}

	return ret;
}