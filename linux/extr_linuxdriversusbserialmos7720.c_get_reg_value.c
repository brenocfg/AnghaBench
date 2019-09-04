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
typedef  enum mos_regs { ____Placeholder_mos_regs } mos_regs ;
typedef  int __u16 ;

/* Variables and functions */
 int MOS7720_DPR ; 
 int MOS7720_SP1_REG ; 

__attribute__((used)) static inline __u16 get_reg_value(enum mos_regs reg,
				  unsigned int serial_portnum)
{
	if (reg >= MOS7720_SP1_REG)	/* control reg */
		return 0x0000;

	else if (reg >= MOS7720_DPR)	/* parallel port reg (7715 only) */
		return 0x0100;

	else			      /* serial port reg */
		return (serial_portnum + 2) << 8;
}