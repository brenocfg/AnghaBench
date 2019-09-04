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
typedef  int u16 ;
struct mgsl_struct {scalar_t__ bus_type; } ;

/* Variables and functions */
 int BIT0 ; 
 int BIT1 ; 
 int /*<<< orphan*/  CMCR ; 
 int /*<<< orphan*/  HCR ; 
 int /*<<< orphan*/  IOCR ; 
 scalar_t__ MGSL_BUS_TYPE_PCI ; 
 int /*<<< orphan*/  TC0R ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void usc_enable_async_clock( struct mgsl_struct *info, u32 data_rate )
{
	if ( data_rate )	{
		/*
		 * Clock mode Control Register (CMCR)
		 * 
		 * <15..14>     00      counter 1 Disabled
		 * <13..12>     00      counter 0 Disabled
		 * <11..10>     11      BRG1 Input is TxC Pin
		 * <9..8>       11      BRG0 Input is TxC Pin
		 * <7..6>       01      DPLL Input is BRG1 Output
		 * <5..3>       100     TxCLK comes from BRG0
		 * <2..0>       100     RxCLK comes from BRG0
		 *
		 * 0000 1111 0110 0100 = 0x0f64
		 */
		
		usc_OutReg( info, CMCR, 0x0f64 );


		/*
		 * Write 16-bit Time Constant for BRG0
		 * Time Constant = (ClkSpeed / data_rate) - 1
		 * ClkSpeed = 921600 (ISA), 691200 (PCI)
		 */

		if ( info->bus_type == MGSL_BUS_TYPE_PCI )
			usc_OutReg( info, TC0R, (u16)((691200/data_rate) - 1) );
		else
			usc_OutReg( info, TC0R, (u16)((921600/data_rate) - 1) );

		
		/*
		 * Hardware Configuration Register (HCR)
		 * Clear Bit 1, BRG0 mode = Continuous
		 * Set Bit 0 to enable BRG0.
		 */

		usc_OutReg( info, HCR,
			    (u16)((usc_InReg( info, HCR ) & ~BIT1) | BIT0) );


		/* Input/Output Control Reg, <2..0> = 100, Drive RxC pin with BRG0 */

		usc_OutReg( info, IOCR,
			    (u16)((usc_InReg(info, IOCR) & 0xfff8) | 0x0004) );
	} else {
		/* data rate == 0 so turn off BRG0 */
		usc_OutReg( info, HCR, (u16)(usc_InReg( info, HCR ) & ~BIT0) );
	}

}