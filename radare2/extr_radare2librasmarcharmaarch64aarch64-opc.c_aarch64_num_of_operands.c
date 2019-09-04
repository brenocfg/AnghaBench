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
typedef  enum aarch64_opnd { ____Placeholder_aarch64_opnd } aarch64_opnd ;
struct TYPE_3__ {int* operands; } ;
typedef  TYPE_1__ aarch64_opcode ;

/* Variables and functions */
 int AARCH64_MAX_OPND_NUM ; 
 int const AARCH64_OPND_NIL ; 
 int /*<<< orphan*/  assert (int) ; 

int
aarch64_num_of_operands (const aarch64_opcode *opcode)
{
  int i = 0;
  const enum aarch64_opnd *opnds = opcode->operands;
  while (opnds[i++] != AARCH64_OPND_NIL)
    ;
  --i;
  assert (i >= 0 && i <= AARCH64_MAX_OPND_NUM);
  return i;
}