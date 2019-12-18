#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* opcode; struct TYPE_4__* next; } ;
typedef  TYPE_1__ sparc_opcode_hash ;
struct TYPE_5__ {unsigned long match; unsigned long lose; int flags; } ;
typedef  TYPE_2__ sparc_opcode ;

/* Variables and functions */
 int F_DELAYED ; 
 size_t HASH_INSN (unsigned long) ; 
 TYPE_1__** opcode_hash_table ; 

__attribute__((used)) static int
is_delayed_branch (unsigned long insn)
{
  sparc_opcode_hash *op;

  for (op = opcode_hash_table[HASH_INSN (insn)]; op; op = op->next)
    {
      const sparc_opcode *opcode = op->opcode;

      if ((opcode->match & insn) == opcode->match && (opcode->lose & insn) == 0) {
	      return opcode->flags & F_DELAYED;
      }
    }
  return 0;
}