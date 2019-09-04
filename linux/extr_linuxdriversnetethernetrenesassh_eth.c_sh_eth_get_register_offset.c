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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
#define  SH_ETH_REG_FAST_RCAR 132 
#define  SH_ETH_REG_FAST_RZ 131 
#define  SH_ETH_REG_FAST_SH3_SH2 130 
#define  SH_ETH_REG_FAST_SH4 129 
#define  SH_ETH_REG_GIGABIT 128 
 int /*<<< orphan*/ * sh_eth_offset_fast_rcar ; 
 int /*<<< orphan*/ * sh_eth_offset_fast_rz ; 
 int /*<<< orphan*/ * sh_eth_offset_fast_sh3_sh2 ; 
 int /*<<< orphan*/ * sh_eth_offset_fast_sh4 ; 
 int /*<<< orphan*/ * sh_eth_offset_gigabit ; 

__attribute__((used)) static const u16 *sh_eth_get_register_offset(int register_type)
{
	const u16 *reg_offset = NULL;

	switch (register_type) {
	case SH_ETH_REG_GIGABIT:
		reg_offset = sh_eth_offset_gigabit;
		break;
	case SH_ETH_REG_FAST_RZ:
		reg_offset = sh_eth_offset_fast_rz;
		break;
	case SH_ETH_REG_FAST_RCAR:
		reg_offset = sh_eth_offset_fast_rcar;
		break;
	case SH_ETH_REG_FAST_SH4:
		reg_offset = sh_eth_offset_fast_sh4;
		break;
	case SH_ETH_REG_FAST_SH3_SH2:
		reg_offset = sh_eth_offset_fast_sh3_sh2;
		break;
	}

	return reg_offset;
}