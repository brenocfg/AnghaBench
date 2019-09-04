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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ulpiview; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_writel (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* usb_dr_regs ; 

int write_ulpi(u8 addr, u8 data)
{
	u32 temp;

	temp = 0x60000000 | (addr << 16) | data;
	fsl_writel(temp, &usb_dr_regs->ulpiview);
	return 0;
}