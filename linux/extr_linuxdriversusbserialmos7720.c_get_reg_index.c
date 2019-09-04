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

__attribute__((used)) static inline __u16 get_reg_index(enum mos_regs reg)
{
	static const __u16 mos7715_index_lookup_table[] = {
		0x00,		/* MOS7720_THR */
		0x00,		/* MOS7720_RHR */
		0x01,		/* MOS7720_IER */
		0x02,		/* MOS7720_FCR */
		0x02,		/* MOS7720_ISR */
		0x03,		/* MOS7720_LCR */
		0x04,		/* MOS7720_MCR */
		0x05,		/* MOS7720_LSR */
		0x06,		/* MOS7720_MSR */
		0x07,		/* MOS7720_SPR */
		0x00,		/* MOS7720_DLL */
		0x01,		/* MOS7720_DLM */
		0x00,		/* MOS7720_DPR */
		0x01,		/* MOS7720_DSR */
		0x02,		/* MOS7720_DCR */
		0x0a,		/* MOS7720_ECR */
		0x01,		/* MOS7720_SP1_REG */
		0x02,		/* MOS7720_SP2_REG (7720 only) */
		0x04,		/* MOS7720_PP_REG (7715 only) */
		0x08,		/* MOS7720_SP_CONTROL_REG */
	};
	return mos7715_index_lookup_table[reg];
}