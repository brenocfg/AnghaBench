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
struct arc_operand_value {size_t type; int value; } ;
struct arc_operand {int dummy; } ;
struct arc_ext_operand_value {struct arc_ext_operand_value* next; struct arc_operand_value const operand; } ;

/* Variables and functions */
 struct arc_ext_operand_value* arc_ext_operands ; 
 struct arc_operand const* arc_operands ; 
 struct arc_operand_value* arc_suffixes ; 
 int arc_suffixes_count ; 

const struct arc_operand_value *
arc_opcode_lookup_suffix (const struct arc_operand *type, int value)
{
  const struct arc_operand_value *v,*end;
  struct arc_ext_operand_value *ext_oper = arc_ext_operands;
  while (ext_oper)
    {
	  if (type == &arc_operands[ext_oper->operand.type] && value == ext_oper->operand.value) {
		  return (&ext_oper->operand);
	  }
	  ext_oper = ext_oper->next;
    }

  /* ??? This is a little slow and can be speeded up.  */
    for (v = arc_suffixes, end = arc_suffixes + arc_suffixes_count; v < end; ++v) {
	    if (type == &arc_operands[v->type] && value == v->value) {
		    return v;
	    }
    }
    return 0;
}