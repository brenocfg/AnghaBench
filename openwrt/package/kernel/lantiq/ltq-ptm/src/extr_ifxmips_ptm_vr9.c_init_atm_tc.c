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

/* Variables and functions */
 int /*<<< orphan*/  DREG_AR_CFG0 ; 
 int /*<<< orphan*/  DREG_AR_CFG1 ; 
 int /*<<< orphan*/  DREG_AR_IDLE0 ; 
 int /*<<< orphan*/  DREG_AR_IDLE1 ; 
 int /*<<< orphan*/  DREG_AT_CFG0 ; 
 int /*<<< orphan*/  DREG_AT_CFG1 ; 
 int /*<<< orphan*/  DREG_AT_IDLE0 ; 
 int /*<<< orphan*/  DREG_AT_IDLE1 ; 
 int /*<<< orphan*/  DREG_B0_LADR ; 
 int /*<<< orphan*/  DREG_B1_LADR ; 
 int /*<<< orphan*/  FFSM_CFG0 ; 
 int /*<<< orphan*/  FFSM_CFG1 ; 
 int /*<<< orphan*/  FFSM_IDLE_HEAD_BC0 ; 
 int /*<<< orphan*/  FFSM_IDLE_HEAD_BC1 ; 
 int /*<<< orphan*/  IFX_REG_W32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFX_REG_W32_MASK (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SFSM_CFG0 ; 
 int /*<<< orphan*/  SFSM_CFG1 ; 
 int /*<<< orphan*/  SFSM_PGCNT0 ; 
 int /*<<< orphan*/  SFSM_PGCNT1 ; 

__attribute__((used)) static inline void init_atm_tc(void)
{
    IFX_REG_W32(0x00010040, SFSM_CFG0);
    IFX_REG_W32(0x00010040, SFSM_CFG1);
    IFX_REG_W32(0x00020000, SFSM_PGCNT0);
    IFX_REG_W32(0x00020000, SFSM_PGCNT1);
    IFX_REG_W32(0x00000000, DREG_AT_IDLE0);
    IFX_REG_W32(0x00000000, DREG_AT_IDLE1);
    IFX_REG_W32(0x00000000, DREG_AR_IDLE0);
    IFX_REG_W32(0x00000000, DREG_AR_IDLE1);
    IFX_REG_W32(0x0000080C, DREG_B0_LADR);
    IFX_REG_W32(0x0000080C, DREG_B1_LADR);

    IFX_REG_W32(0x000001F0, DREG_AR_CFG0);
    IFX_REG_W32(0x000001F0, DREG_AR_CFG1);
    IFX_REG_W32(0x000001E0, DREG_AT_CFG0);
    IFX_REG_W32(0x000001E0, DREG_AT_CFG1);

    /*  clear sync state    */
    //IFX_REG_W32(0, SFSM_STATE0);
    //IFX_REG_W32(0, SFSM_STATE1);

    IFX_REG_W32_MASK(0, 1 << 14, SFSM_CFG0);    //  enable SFSM storing
    IFX_REG_W32_MASK(0, 1 << 14, SFSM_CFG1);

    IFX_REG_W32_MASK(0, 1 << 15, SFSM_CFG0);    //  HW keep the IDLE cells in RTHA buffer
    IFX_REG_W32_MASK(0, 1 << 15, SFSM_CFG1);

    IFX_REG_W32(0xF0D10000, FFSM_IDLE_HEAD_BC0);
    IFX_REG_W32(0xF0D10000, FFSM_IDLE_HEAD_BC1);
    IFX_REG_W32(0x00030028, FFSM_CFG0);         //  Force_idle
    IFX_REG_W32(0x00030028, FFSM_CFG1);
}