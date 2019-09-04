#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int base_hi; } ;
typedef  TYPE_1__ imm_struct ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*) ; 
 int r_ecr (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void ecp_sync(imm_struct *dev)
{
	int i, ppb_hi = dev->base_hi;

	if (ppb_hi == 0)
		return;

	if ((r_ecr(ppb_hi) & 0xe0) == 0x60) {	/* mode 011 == ECP fifo mode */
		for (i = 0; i < 100; i++) {
			if (r_ecr(ppb_hi) & 0x01)
				return;
			udelay(5);
		}
		printk("imm: ECP sync failed as data still present in FIFO.\n");
	}
}