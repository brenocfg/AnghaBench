#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* regs; int opcode; int* cexp; TYPE_1__* code; } ;
struct TYPE_3__ {int nr_operands; int* fields; } ;

/* Variables and functions */
#define  FMT_RLC_CONST16 130 
#define  FMT_RLC_D 129 
#define  FMT_RLC_S1 128 
 TYPE_2__ dec_insn ; 

__attribute__((used)) static void
decode_rlc ()
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i) {
	  switch (dec_insn.code->fields[i]) {
	  case FMT_RLC_D:
		  dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
		  break;

	  case FMT_RLC_CONST16:
		  dec_insn.cexp[i] = (dec_insn.opcode & 0x0ffff000) >> 12;
		  break;

	  case FMT_RLC_S1:
		  dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
		  break;
	  }
  }
}