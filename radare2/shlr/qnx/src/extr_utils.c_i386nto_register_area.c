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
typedef  int ut32 ;

/* Variables and functions */
 int I387_FCTRL_REGNUM ; 
 int I387_FISEG_REGNUM ; 
 int I387_FOP_REGNUM ; 
 int I387_MXCSR_REGNUM ; 
 int I387_ST0_REGNUM ; 
 int I387_XMM0_REGNUM ; 
 int NTO_REG_FLOAT ; 
 int NTO_REG_GENERAL ; 
 int NUM_GPREGS ; 
 int X86_CPU_FXSR ; 
 int i386nto_reg_offset (int) ; 
 int nto_cpuinfo_flags ; 
 scalar_t__ nto_cpuinfo_valid ; 

int i386nto_register_area (int regno, int regset, ut32 *off) {
	*off = 0;
	if (regset == NTO_REG_GENERAL) {
		if (regno == -1)
			return NUM_GPREGS * 4;

		*off = i386nto_reg_offset (regno);
		if (*off == -1)
			return 0;
		return 4;
	} else if (regset == NTO_REG_FLOAT) {
		ut32 off_adjust, regsize, regset_size, regno_base;
		/* The following are flags indicating number in our fxsave_area.  */
		int first_four = (regno >= I387_FCTRL_REGNUM && regno <= I387_FISEG_REGNUM);
		int second_four = (regno > I387_FISEG_REGNUM && regno <= I387_FOP_REGNUM);
		int st_reg = (regno >= I387_ST0_REGNUM && regno < I387_ST0_REGNUM + 8);
		int xmm_reg = (regno >= I387_XMM0_REGNUM && regno < I387_MXCSR_REGNUM);
#if 0
      if (nto_cpuinfo_valid && nto_cpuinfo_flags | X86_CPU_FXSR)
	  {
#endif
		regset_size = 512;
		/* fxsave_area structure.  */
		if (first_four) {
			/* fpu_control_word, fpu_status_word, fpu_tag_word, fpu_operand
registers.  */
			regsize = 2; /* Two bytes each.  */
			off_adjust = 0;
			regno_base = I387_FCTRL_REGNUM;
		} else if (second_four) {
			/* fpu_ip, fpu_cs, fpu_op, fpu_ds registers.  */
			regsize = 4;
			off_adjust = 8;
			regno_base = I387_FISEG_REGNUM + 1;
		} else if (st_reg) {
			/* ST registers.  */
			regsize = 16;
			off_adjust = 32;
			regno_base = I387_ST0_REGNUM;
		} else if (xmm_reg) {
			/* XMM registers.  */
			regsize = 16;
			off_adjust = 160;
			regno_base = I387_XMM0_REGNUM;
		} else if (regno == I387_MXCSR_REGNUM) {
			regsize = 4;
			off_adjust = 24;
			regno_base = I387_MXCSR_REGNUM;
		} else {
			/* Whole regset.  */
			off_adjust = 0;
			regno_base = 0;
			regsize = regset_size;
		}
#if 0
	}
      else
	{
	  regset_size = 108;
	  /* fsave_area structure.  */
	  if (first_four || second_four)
	    {
	      /* fpu_control_word, ... , fpu_ds registers.  */
	      regsize = 4;
	      off_adjust = 0;
	      regno_base = I387_FCTRL_REGNUM;
	    }
	  else if (st_reg)
	    {
	      /* One of ST registers.  */
	      regsize = 10;
	      off_adjust = 7 * 4;
	      regno_base = I387_ST0_REGNUM;
	    }
	  else
	    {
	      /* Whole regset.  */
	      off_adjust = 0;
	      regno_base = 0;
	      regsize = regset_size;
	    }
	}
#endif

		*off = (regno != -1) ? off_adjust + (regno - regno_base) * regsize : 0;
		return regsize;
	}
	return -1;
}