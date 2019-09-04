#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* detail; } ;
typedef  TYPE_4__ cs_insn ;
struct TYPE_7__ {TYPE_1__* operands; } ;
struct TYPE_8__ {TYPE_2__ arm64; } ;
struct TYPE_6__ {unsigned int reg; } ;

/* Variables and functions */
 unsigned int ARM64_REG_B0 ; 
 unsigned int ARM64_REG_B31 ; 
 unsigned int ARM64_REG_H0 ; 
 unsigned int ARM64_REG_H31 ; 
 unsigned int ARM64_REG_Q0 ; 
 unsigned int ARM64_REG_Q31 ; 
 unsigned int ARM64_REG_S0 ; 
 unsigned int ARM64_REG_S31 ; 
 unsigned int ARM64_REG_W0 ; 
 unsigned int ARM64_REG_W30 ; 
 unsigned int ARM64_REG_WZR ; 

__attribute__((used)) static int regsize64(cs_insn *insn, int n) {
	unsigned int reg = insn->detail->arm64.operands[n].reg;
	if ( (reg >= ARM64_REG_S0 && reg <= ARM64_REG_S31) ||
		(reg >= ARM64_REG_W0 && reg <= ARM64_REG_W30) ||
		reg == ARM64_REG_WZR) {
		return 4;
	}
	if (reg >= ARM64_REG_B0 && reg <= ARM64_REG_B31) {
		return 1;
	}
	if (reg >= ARM64_REG_H0 && reg <= ARM64_REG_H31) {
		return 2;
	}
	if (reg >= ARM64_REG_Q0 && reg <= ARM64_REG_Q31) {
		return 16;
	}
	return 8;
}