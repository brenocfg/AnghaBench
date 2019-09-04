#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int f_nscns; } ;
struct r_bin_coff_obj {TYPE_2__* scn_hdrs; TYPE_1__ hdr; } ;
struct coff_symbol {int n_scnum; scalar_t__ n_value; } ;
struct TYPE_7__ {scalar_t__ paddr; } ;
struct TYPE_6__ {scalar_t__ s_scnptr; } ;
typedef  TYPE_3__ RBinAddr ;

/* Variables and functions */

__attribute__((used)) static int r_coff_rebase_sym(struct r_bin_coff_obj *obj, RBinAddr *addr, struct coff_symbol *sym) {
	if (sym->n_scnum < 1 || sym->n_scnum > obj->hdr.f_nscns) {
		return 0;
	}
	addr->paddr = obj->scn_hdrs[sym->n_scnum - 1].s_scnptr + sym->n_value;
	return 1;
}