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
struct ud_operand {scalar_t__ type; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ UD_OP_REG ; 
 scalar_t__ UD_R_AL ; 
 scalar_t__ UD_R_R15 ; 

int
ud_opr_is_gpr(const struct ud_operand *opr)
{
  return opr->type == UD_OP_REG && 
         opr->base >= UD_R_AL   &&
         opr->base <= UD_R_R15;
}