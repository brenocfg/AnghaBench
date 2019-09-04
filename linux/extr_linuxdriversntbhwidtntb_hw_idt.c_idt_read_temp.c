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
typedef  int u32 ;
struct idt_ntb_dev {int dummy; } ;

/* Variables and functions */
 int GET_FIELD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDT_SW_TMPSTS ; 
 int /*<<< orphan*/  TMPSTS_TEMP ; 
 int idt_sw_read (struct idt_ntb_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idt_read_temp(struct idt_ntb_dev *ndev, unsigned char *val,
			  unsigned char *frac)
{
	u32 data;

	/* Read the data from TEMP field of the TMPSTS register */
	data = idt_sw_read(ndev, IDT_SW_TMPSTS);
	data = GET_FIELD(TMPSTS_TEMP, data);
	/* TEMP field has one fractional bit and seven integer bits */
	*val = data >> 1;
	*frac = ((data & 0x1) ? 5 : 0);
}