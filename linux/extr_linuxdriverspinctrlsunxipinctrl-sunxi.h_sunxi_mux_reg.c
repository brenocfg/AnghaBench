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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int BANK_MEM_SIZE ; 
 int MUX_PINS_PER_REG ; 
 scalar_t__ MUX_REGS_OFFSET ; 
 int PINS_PER_BANK ; 
 int round_down (int,int) ; 

__attribute__((used)) static inline u32 sunxi_mux_reg(u16 pin)
{
	u8 bank = pin / PINS_PER_BANK;
	u32 offset = bank * BANK_MEM_SIZE;
	offset += MUX_REGS_OFFSET;
	offset += pin % PINS_PER_BANK / MUX_PINS_PER_REG * 0x04;
	return round_down(offset, 4);
}