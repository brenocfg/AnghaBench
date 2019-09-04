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
typedef  int u32 ;
struct cas {scalar_t__ regs; } ;
struct TYPE_3__ {int val; int mask; int outarg; int outop; int fnext; int foff; int snext; int soff; int op; int outmask; int outshift; int outenab; scalar_t__ note; } ;
typedef  TYPE_1__ cas_hp_inst_t ;

/* Variables and functions */
 int CAS_BASE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HP_INSTR_RAM_HI_MASK ; 
 int /*<<< orphan*/  HP_INSTR_RAM_HI_VAL ; 
 int /*<<< orphan*/  HP_INSTR_RAM_LOW_OUTARG ; 
 int /*<<< orphan*/  HP_INSTR_RAM_LOW_OUTEN ; 
 int /*<<< orphan*/  HP_INSTR_RAM_LOW_OUTMASK ; 
 int /*<<< orphan*/  HP_INSTR_RAM_LOW_OUTSHIFT ; 
 int /*<<< orphan*/  HP_INSTR_RAM_MID_FNEXT ; 
 int /*<<< orphan*/  HP_INSTR_RAM_MID_FOFF ; 
 int /*<<< orphan*/  HP_INSTR_RAM_MID_OP ; 
 int /*<<< orphan*/  HP_INSTR_RAM_MID_OUTARG ; 
 int /*<<< orphan*/  HP_INSTR_RAM_MID_OUTOP ; 
 int /*<<< orphan*/  HP_INSTR_RAM_MID_SNEXT ; 
 int /*<<< orphan*/  HP_INSTR_RAM_MID_SOFF ; 
 scalar_t__ REG_HP_INSTR_RAM_ADDR ; 
 scalar_t__ REG_HP_INSTR_RAM_DATA_HI ; 
 scalar_t__ REG_HP_INSTR_RAM_DATA_LOW ; 
 scalar_t__ REG_HP_INSTR_RAM_DATA_MID ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cas_load_firmware(struct cas *cp, cas_hp_inst_t *firmware)
{
	cas_hp_inst_t *inst;
	u32 val;
	int i;

	i = 0;
	while ((inst = firmware) && inst->note) {
		writel(i, cp->regs + REG_HP_INSTR_RAM_ADDR);

		val = CAS_BASE(HP_INSTR_RAM_HI_VAL, inst->val);
		val |= CAS_BASE(HP_INSTR_RAM_HI_MASK, inst->mask);
		writel(val, cp->regs + REG_HP_INSTR_RAM_DATA_HI);

		val = CAS_BASE(HP_INSTR_RAM_MID_OUTARG, inst->outarg >> 10);
		val |= CAS_BASE(HP_INSTR_RAM_MID_OUTOP, inst->outop);
		val |= CAS_BASE(HP_INSTR_RAM_MID_FNEXT, inst->fnext);
		val |= CAS_BASE(HP_INSTR_RAM_MID_FOFF, inst->foff);
		val |= CAS_BASE(HP_INSTR_RAM_MID_SNEXT, inst->snext);
		val |= CAS_BASE(HP_INSTR_RAM_MID_SOFF, inst->soff);
		val |= CAS_BASE(HP_INSTR_RAM_MID_OP, inst->op);
		writel(val, cp->regs + REG_HP_INSTR_RAM_DATA_MID);

		val = CAS_BASE(HP_INSTR_RAM_LOW_OUTMASK, inst->outmask);
		val |= CAS_BASE(HP_INSTR_RAM_LOW_OUTSHIFT, inst->outshift);
		val |= CAS_BASE(HP_INSTR_RAM_LOW_OUTEN, inst->outenab);
		val |= CAS_BASE(HP_INSTR_RAM_LOW_OUTARG, inst->outarg);
		writel(val, cp->regs + REG_HP_INSTR_RAM_DATA_LOW);
		++firmware;
		++i;
	}
}