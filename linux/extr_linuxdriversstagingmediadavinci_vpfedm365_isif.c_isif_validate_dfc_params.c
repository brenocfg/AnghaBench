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
struct vpfe_isif_dfc {int corr_whole_line; scalar_t__ def_level_shift; scalar_t__ def_sat_level; int num_vdefects; TYPE_1__* table; int /*<<< orphan*/  en; } ;
struct TYPE_2__ {scalar_t__ pos_vert; scalar_t__ pos_horz; } ;

/* Variables and functions */
 scalar_t__ DM365_ISIF_MAX_DFCMEM0 ; 
 scalar_t__ DM365_ISIF_MAX_DFCMEM1 ; 
 scalar_t__ DM365_ISIF_MAX_VDFLSFT ; 
 scalar_t__ DM365_ISIF_MAX_VDFSLV ; 
 int EINVAL ; 
 int VPFE_ISIF_VDFC_TABLE_SIZE ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int isif_validate_dfc_params(struct vpfe_isif_dfc *dfc)
{
	int err = -EINVAL;
	int i;

	if (!dfc->en)
		return 0;

	if (dfc->corr_whole_line > 1) {
		pr_err("Invalid corr_whole_line value\n");
		return err;
	}

	if (dfc->def_level_shift > DM365_ISIF_MAX_VDFLSFT) {
		pr_err("Invalid def_level_shift value\n");
		return err;
	}

	if (dfc->def_sat_level > DM365_ISIF_MAX_VDFSLV) {
		pr_err("Invalid def_sat_level value\n");
		return err;
	}

	if (!dfc->num_vdefects ||
	    dfc->num_vdefects > VPFE_ISIF_VDFC_TABLE_SIZE) {
		pr_err("Invalid num_vdefects value\n");
		return err;
	}

	for (i = 0; i < VPFE_ISIF_VDFC_TABLE_SIZE; i++) {
		if (dfc->table[i].pos_vert > DM365_ISIF_MAX_DFCMEM0) {
			pr_err("Invalid pos_vert value\n");
			return err;
		}
		if (dfc->table[i].pos_horz > DM365_ISIF_MAX_DFCMEM1) {
			pr_err("Invalid pos_horz value\n");
			return err;
		}
	}

	return 0;
}