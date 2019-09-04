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
struct device {int dummy; } ;

/* Variables and functions */
#define  REG_ASR56K 159 
#define  REG_ASR76K 158 
#define  REG_ASRCCR 157 
#define  REG_ASRCDR1 156 
#define  REG_ASRCDR2 155 
#define  REG_ASRCFG 154 
#define  REG_ASRCNCR 153 
#define  REG_ASRCSR 152 
#define  REG_ASRCTR 151 
#define  REG_ASRDIA 150 
#define  REG_ASRDIB 149 
#define  REG_ASRDIC 148 
#define  REG_ASRIDRHA 147 
#define  REG_ASRIDRHB 146 
#define  REG_ASRIDRHC 145 
#define  REG_ASRIDRLA 144 
#define  REG_ASRIDRLB 143 
#define  REG_ASRIDRLC 142 
#define  REG_ASRIER 141 
#define  REG_ASRMCR1A 140 
#define  REG_ASRMCR1B 139 
#define  REG_ASRMCR1C 138 
#define  REG_ASRMCRA 137 
#define  REG_ASRMCRB 136 
#define  REG_ASRMCRC 135 
#define  REG_ASRPM1 134 
#define  REG_ASRPM2 133 
#define  REG_ASRPM3 132 
#define  REG_ASRPM4 131 
#define  REG_ASRPM5 130 
#define  REG_ASRSTR 129 
#define  REG_ASRTFR1 128 

__attribute__((used)) static bool fsl_asrc_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case REG_ASRCTR:
	case REG_ASRIER:
	case REG_ASRCNCR:
	case REG_ASRCFG:
	case REG_ASRCSR:
	case REG_ASRCDR1:
	case REG_ASRCDR2:
	case REG_ASRSTR:
	case REG_ASRPM1:
	case REG_ASRPM2:
	case REG_ASRPM3:
	case REG_ASRPM4:
	case REG_ASRPM5:
	case REG_ASRTFR1:
	case REG_ASRCCR:
	case REG_ASRDIA:
	case REG_ASRDIB:
	case REG_ASRDIC:
	case REG_ASRIDRHA:
	case REG_ASRIDRLA:
	case REG_ASRIDRHB:
	case REG_ASRIDRLB:
	case REG_ASRIDRHC:
	case REG_ASRIDRLC:
	case REG_ASR76K:
	case REG_ASR56K:
	case REG_ASRMCRA:
	case REG_ASRMCRB:
	case REG_ASRMCRC:
	case REG_ASRMCR1A:
	case REG_ASRMCR1B:
	case REG_ASRMCR1C:
		return true;
	default:
		return false;
	}
}