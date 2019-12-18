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
typedef  int u32 ;
struct trn_conf {unsigned long vm_pgt_phys; } ;
struct hw {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTPAHX ; 
 int /*<<< orphan*/  PTPALX ; 
 int /*<<< orphan*/  TRNCTL ; 
 int /*<<< orphan*/  TRNIS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,int) ; 
 int upper_32_bits (unsigned long) ; 

__attribute__((used)) static int hw_trn_init(struct hw *hw, const struct trn_conf *info)
{
	u32 trnctl;
	u32 ptp_phys_low, ptp_phys_high;

	/* Set up device page table */
	if ((~0UL) == info->vm_pgt_phys) {
		dev_err(hw->card->dev,
			"Wrong device page table page address!\n");
		return -1;
	}

	trnctl = 0x13;  /* 32-bit, 4k-size page */
	ptp_phys_low = (u32)info->vm_pgt_phys;
	ptp_phys_high = upper_32_bits(info->vm_pgt_phys);
	if (sizeof(void *) == 8) /* 64bit address */
		trnctl |= (1 << 2);
#if 0 /* Only 4k h/w pages for simplicitiy */
#if PAGE_SIZE == 8192
	trnctl |= (1<<5);
#endif
#endif
	hw_write_20kx(hw, PTPALX, ptp_phys_low);
	hw_write_20kx(hw, PTPAHX, ptp_phys_high);
	hw_write_20kx(hw, TRNCTL, trnctl);
	hw_write_20kx(hw, TRNIS, 0x200c01); /* really needed? */

	return 0;
}