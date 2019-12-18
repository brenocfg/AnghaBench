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
 int OPERANDS ; 
 int /*<<< orphan*/  OP_NONE ; 
 scalar_t__ addrwb_p ; 
 scalar_t__ arc_cond_p ; 
 scalar_t__ flag_p ; 
 scalar_t__ flagshimm_handled_p ; 
 scalar_t__ jumpflags_p ; 
 scalar_t__ limm_p ; 
 int /*<<< orphan*/ * ls_operand ; 
 scalar_t__ nullify ; 
 scalar_t__ nullify_p ; 
 scalar_t__ shimm_p ; 

void
arc_opcode_init_insert (void)
{
  int i;

  for (i = 0; i < OPERANDS; i++) {
	  ls_operand[i] = OP_NONE;
  }

  flag_p = 0;
  flagshimm_handled_p = 0;
  arc_cond_p = 0;
  addrwb_p = 0;
  shimm_p = 0;
  limm_p = 0;
  jumpflags_p = 0;
  nullify_p = 0;
  nullify = 0; /* The default is important.  */
}