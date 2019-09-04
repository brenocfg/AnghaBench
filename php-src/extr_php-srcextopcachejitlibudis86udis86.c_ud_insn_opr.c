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
struct ud_operand {scalar_t__ type; } ;
struct ud {struct ud_operand const* operand; } ;

/* Variables and functions */
 scalar_t__ UD_NONE ; 

const struct ud_operand*
ud_insn_opr(const struct ud *u, unsigned int n)
{
  if (n > 3 || u->operand[n].type == UD_NONE) {
    return NULL; 
  } else {
    return &u->operand[n];
  }
}