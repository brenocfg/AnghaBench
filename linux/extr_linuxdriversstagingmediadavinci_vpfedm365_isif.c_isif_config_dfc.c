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
typedef  int u32 ;
struct vpfe_isif_dfc {int corr_mode; int def_level_shift; int def_sat_level; int num_vdefects; TYPE_1__* table; scalar_t__ corr_whole_line; int /*<<< orphan*/  en; } ;
struct TYPE_4__ {int /*<<< orphan*/  base_addr; } ;
struct vpfe_isif_device {TYPE_2__ isif_cfg; } ;
struct TYPE_3__ {int pos_vert; int pos_horz; int level_at_pos; int level_up_pixels; int level_low_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFCCTL ; 
 int /*<<< orphan*/  DFCMEM0 ; 
 int /*<<< orphan*/  DFCMEM1 ; 
 int /*<<< orphan*/  DFCMEM2 ; 
 int /*<<< orphan*/  DFCMEM3 ; 
 int /*<<< orphan*/  DFCMEM4 ; 
 int /*<<< orphan*/  DFCMEMCTL ; 
 int DM365_ISIF_DFCMRD_MEMORY_READ ; 
 int DM365_ISIF_DFCMWR_MEMORY_WRITE ; 
 int DM365_ISIF_MAX_DFCMEM1 ; 
 int ISIF_DFCMEMCTL_DFCMARST_SHIFT ; 
 int ISIF_VDFC_CORR_MOD_MASK ; 
 int ISIF_VDFC_CORR_MOD_SHIFT ; 
 int ISIF_VDFC_CORR_WHOLE_LN_SHIFT ; 
 int ISIF_VDFC_EN_SHIFT ; 
 int ISIF_VDFC_LEVEL_SHFT_MASK ; 
 int ISIF_VDFC_LEVEL_SHFT_SHIFT ; 
 int ISIF_VDFC_POS_MASK ; 
 int ISIF_VDFC_SAT_LEVEL_MASK ; 
 int /*<<< orphan*/  VDFSATLV ; 
 int VPFE_ISIF_VDFC_HORZ_INTERPOL_IF_SAT ; 
 int VPFE_ISIF_VDFC_NORMAL ; 
 int VPFE_ISIF_VDFC_TABLE_SIZE ; 
 int /*<<< orphan*/  isif_merge (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int isif_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isif_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void
isif_config_dfc(struct vpfe_isif_device *isif, struct vpfe_isif_dfc *vdfc)
{
#define DFC_WRITE_WAIT_COUNT	1000
	u32 count = DFC_WRITE_WAIT_COUNT;
	u32 val;
	int i;

	if (!vdfc->en)
		return;

	/* Correction mode */
	val = (vdfc->corr_mode & ISIF_VDFC_CORR_MOD_MASK) <<
	       ISIF_VDFC_CORR_MOD_SHIFT;

	/* Correct whole line or partial */
	if (vdfc->corr_whole_line)
		val |= 1 << ISIF_VDFC_CORR_WHOLE_LN_SHIFT;

	/* level shift value */
	val |= (vdfc->def_level_shift & ISIF_VDFC_LEVEL_SHFT_MASK) <<
		ISIF_VDFC_LEVEL_SHFT_SHIFT;

	isif_write(isif->isif_cfg.base_addr, val, DFCCTL);

	/* Defect saturation level */
	val = vdfc->def_sat_level & ISIF_VDFC_SAT_LEVEL_MASK;
	isif_write(isif->isif_cfg.base_addr, val, VDFSATLV);

	isif_write(isif->isif_cfg.base_addr, vdfc->table[0].pos_vert &
		   ISIF_VDFC_POS_MASK, DFCMEM0);
	isif_write(isif->isif_cfg.base_addr, vdfc->table[0].pos_horz &
		   ISIF_VDFC_POS_MASK, DFCMEM1);
	if (vdfc->corr_mode == VPFE_ISIF_VDFC_NORMAL ||
	    vdfc->corr_mode == VPFE_ISIF_VDFC_HORZ_INTERPOL_IF_SAT) {
		isif_write(isif->isif_cfg.base_addr,
			   vdfc->table[0].level_at_pos, DFCMEM2);
		isif_write(isif->isif_cfg.base_addr,
			   vdfc->table[0].level_up_pixels, DFCMEM3);
		isif_write(isif->isif_cfg.base_addr,
			   vdfc->table[0].level_low_pixels, DFCMEM4);
	}

	val = isif_read(isif->isif_cfg.base_addr, DFCMEMCTL);
	/* set DFCMARST and set DFCMWR */
	val |= 1 << ISIF_DFCMEMCTL_DFCMARST_SHIFT;
	val |= 1;
	isif_write(isif->isif_cfg.base_addr, val, DFCMEMCTL);

	while (count && (isif_read(isif->isif_cfg.base_addr, DFCMEMCTL) & 0x01))
		count--;

	val = isif_read(isif->isif_cfg.base_addr, DFCMEMCTL);
	if (!count) {
		pr_debug("defect table write timeout !!\n");
		return;
	}

	for (i = 1; i < vdfc->num_vdefects; i++) {
		isif_write(isif->isif_cfg.base_addr, vdfc->table[i].pos_vert &
			ISIF_VDFC_POS_MASK, DFCMEM0);

		isif_write(isif->isif_cfg.base_addr, vdfc->table[i].pos_horz &
			ISIF_VDFC_POS_MASK, DFCMEM1);

		if (vdfc->corr_mode == VPFE_ISIF_VDFC_NORMAL ||
		    vdfc->corr_mode == VPFE_ISIF_VDFC_HORZ_INTERPOL_IF_SAT) {
			isif_write(isif->isif_cfg.base_addr,
				   vdfc->table[i].level_at_pos, DFCMEM2);
			isif_write(isif->isif_cfg.base_addr,
				   vdfc->table[i].level_up_pixels, DFCMEM3);
			isif_write(isif->isif_cfg.base_addr,
				   vdfc->table[i].level_low_pixels, DFCMEM4);
		}
		val = isif_read(isif->isif_cfg.base_addr, DFCMEMCTL);
		/* clear DFCMARST and set DFCMWR */
		val &= ~(1 << ISIF_DFCMEMCTL_DFCMARST_SHIFT);
		val |= 1;
		isif_write(isif->isif_cfg.base_addr, val, DFCMEMCTL);

		count = DFC_WRITE_WAIT_COUNT;
		while (count && (isif_read(isif->isif_cfg.base_addr,
			DFCMEMCTL) & 0x01))
			count--;

		val = isif_read(isif->isif_cfg.base_addr, DFCMEMCTL);
		if (!count) {
			pr_debug("defect table write timeout !!\n");
			return;
		}
	}
	if (vdfc->num_vdefects < VPFE_ISIF_VDFC_TABLE_SIZE) {
		/* Extra cycle needed */
		isif_write(isif->isif_cfg.base_addr, 0, DFCMEM0);
		isif_write(isif->isif_cfg.base_addr,
			   DM365_ISIF_MAX_DFCMEM1, DFCMEM1);
		isif_write(isif->isif_cfg.base_addr,
			   DM365_ISIF_DFCMWR_MEMORY_WRITE, DFCMEMCTL);
	}
	/* enable VDFC */
	isif_merge(isif->isif_cfg.base_addr, (1 << ISIF_VDFC_EN_SHIFT),
		   (1 << ISIF_VDFC_EN_SHIFT), DFCCTL);

	isif_merge(isif->isif_cfg.base_addr, (1 << ISIF_VDFC_EN_SHIFT),
		   (0 << ISIF_VDFC_EN_SHIFT), DFCCTL);

	isif_write(isif->isif_cfg.base_addr, 0x6, DFCMEMCTL);
	for (i = 0; i < vdfc->num_vdefects; i++) {
		count = DFC_WRITE_WAIT_COUNT;
		while (count &&
			(isif_read(isif->isif_cfg.base_addr, DFCMEMCTL) & 0x2))
			count--;
		val = isif_read(isif->isif_cfg.base_addr, DFCMEMCTL);
		if (!count) {
			pr_debug("defect table write timeout !!\n");
			return;
		}
		isif_write(isif->isif_cfg.base_addr,
			   DM365_ISIF_DFCMRD_MEMORY_READ, DFCMEMCTL);
	}
}