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
 int I386_NUM_FREGS ; 
 int I386_NUM_GREGS ; 
 int I386_SSE_NUM_REGS ; 
 int NTO_REG_END ; 
 int NTO_REG_FLOAT ; 
 int NTO_REG_GENERAL ; 

int i386nto_regset_id (int regno) {
	if (regno == -1)
		return NTO_REG_END;
	if (regno < I386_NUM_GREGS)
		return NTO_REG_GENERAL;
	if (regno < I386_NUM_GREGS + I386_NUM_FREGS)
		return NTO_REG_FLOAT;
	if (regno < I386_SSE_NUM_REGS)
		return NTO_REG_FLOAT; /* We store xmm registers in fxsave_area.  */

	return -1;
}