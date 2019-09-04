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
 scalar_t__ TRANSPORT_CTL ; 
 scalar_t__ TRANSPORT_ENB ; 
 scalar_t__ TRANSPORT_INT ; 
 scalar_t__ VMEM_CTL ; 
 scalar_t__ VMEM_PTPAH ; 
 scalar_t__ VMEM_PTPAL ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*) ; 
 int hw_read_20kx (struct hw*,scalar_t__) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,scalar_t__,int) ; 
 int upper_32_bits (unsigned long) ; 

__attribute__((used)) static int hw_trn_init(struct hw *hw, const struct trn_conf *info)
{
	u32 vmctl, data;
	u32 ptp_phys_low, ptp_phys_high;
	int i;

	/* Set up device page table */
	if ((~0UL) == info->vm_pgt_phys) {
		dev_alert(hw->card->dev,
			  "Wrong device page table page address!!!\n");
		return -1;
	}

	vmctl = 0x80000C0F;  /* 32-bit, 4k-size page */
	ptp_phys_low = (u32)info->vm_pgt_phys;
	ptp_phys_high = upper_32_bits(info->vm_pgt_phys);
	if (sizeof(void *) == 8) /* 64bit address */
		vmctl |= (3 << 8);
	/* Write page table physical address to all PTPAL registers */
	for (i = 0; i < 64; i++) {
		hw_write_20kx(hw, VMEM_PTPAL+(16*i), ptp_phys_low);
		hw_write_20kx(hw, VMEM_PTPAH+(16*i), ptp_phys_high);
	}
	/* Enable virtual memory transfer */
	hw_write_20kx(hw, VMEM_CTL, vmctl);
	/* Enable transport bus master and queueing of request */
	hw_write_20kx(hw, TRANSPORT_CTL, 0x03);
	hw_write_20kx(hw, TRANSPORT_INT, 0x200c01);
	/* Enable transport ring */
	data = hw_read_20kx(hw, TRANSPORT_ENB);
	hw_write_20kx(hw, TRANSPORT_ENB, (data | 0x03));

	return 0;
}