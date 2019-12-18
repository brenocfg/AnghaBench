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
struct arc_operand_value {int type; long value; } ;
struct arc_ext_operand_value {struct arc_ext_operand_value* next; struct arc_operand_value const operand; } ;

/* Variables and functions */
 int REG ; 
 int REG_AC ; 
 struct arc_ext_operand_value* arc_ext_operands ; 
 struct arc_operand_value const* arc_reg_names ; 
 int arc_reg_names_count ; 

__attribute__((used)) static const struct arc_operand_value *
lookup_register (int type, long regno)
{
  const struct arc_operand_value *r,*end;
  struct arc_ext_operand_value *ext_oper = arc_ext_operands;

  while (ext_oper)
    {
	  if (ext_oper->operand.type == type && ext_oper->operand.value == regno) {
		  return (&ext_oper->operand);
	  }
	  ext_oper = ext_oper->next;
    }

    if (type == REG || type == REG_AC) {
	    return &arc_reg_names[regno];
    }

    /* ??? This is a little slow and can be speeded up.  */
    for (r = arc_reg_names, end = arc_reg_names + arc_reg_names_count;
	    r < end; ++r) {
	    if (type == r->type && regno == r->value) {
		    return r;
	    }
    }
    return 0;
}