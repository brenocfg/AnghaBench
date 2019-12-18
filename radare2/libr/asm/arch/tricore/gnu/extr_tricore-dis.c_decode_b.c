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
struct TYPE_4__ {int opcode; unsigned long* cexp; TYPE_1__* code; } ;
struct TYPE_3__ {int nr_operands; int* fields; } ;

/* Variables and functions */
#define  FMT_B_DISP24 128 
 TYPE_2__ dec_insn ; 

__attribute__((used)) static void
decode_b ()
{
  int i;
  unsigned long o1, o2;

  for (i = 0; i < dec_insn.code->nr_operands; ++i) {
	  switch (dec_insn.code->fields[i]) {
	  case FMT_B_DISP24:
		  o1 = (dec_insn.opcode & 0xffff0000) >> 16;
		  o2 = (dec_insn.opcode & 0x0000ff00) << 8;
		  dec_insn.cexp[i] = o1 | o2;
		  break;
	  }
  }
}