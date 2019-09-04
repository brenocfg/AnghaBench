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
typedef  int u16 ;
struct r8152 {int ocp_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  PLA_OCP_GPHY_BASE ; 
 int ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u16 ocp_reg_read(struct r8152 *tp, u16 addr)
{
	u16 ocp_base, ocp_index;

	ocp_base = addr & 0xf000;
	if (ocp_base != tp->ocp_base) {
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_OCP_GPHY_BASE, ocp_base);
		tp->ocp_base = ocp_base;
	}

	ocp_index = (addr & 0x0fff) | 0xb000;
	return ocp_read_word(tp, MCU_TYPE_PLA, ocp_index);
}