#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;

/* Variables and functions */
 int ENODEV ; 
 int ENUM_INT_MASK ; 
 int /*<<< orphan*/  csr_int_mask ; 
 int /*<<< orphan*/ * hc_dev ; 
 int readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zt5550_hc_enable_irq(void)
{
	u8 reg;

	if (hc_dev == NULL)
		return -ENODEV;

	reg = readb(csr_int_mask);
	reg = reg & ~ENUM_INT_MASK;
	writeb(reg, csr_int_mask);
	return 0;
}