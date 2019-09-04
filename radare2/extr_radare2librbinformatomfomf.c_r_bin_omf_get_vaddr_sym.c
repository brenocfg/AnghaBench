#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  long long ut64 ;
struct TYPE_7__ {int nb_section; TYPE_1__** sections; } ;
typedef  TYPE_2__ r_bin_omf_obj ;
struct TYPE_8__ {int seg_idx; long long offset; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {long long vaddr; } ;
typedef  TYPE_3__ OMF_symbol ;

/* Variables and functions */
 long long OMF_BASE_ADDR ; 
 int /*<<< orphan*/  eprintf (char*,int /*<<< orphan*/ ) ; 

ut64 r_bin_omf_get_vaddr_sym(r_bin_omf_obj *obj, OMF_symbol *sym) {
	if (!obj->sections) {
		return 0LL;
	}
	if (sym->seg_idx >= obj->nb_section) {
		eprintf ("Invalid segment index for symbol %s\n", sym->name);
		return 0;
	}
	if (sym->seg_idx == 0) {
		return 0;
	}
	return obj->sections[sym->seg_idx - 1]->vaddr + sym->offset + OMF_BASE_ADDR;
}