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
struct aarch64_opnd_info {int qualifier; scalar_t__ type; } ;
typedef  int aarch64_opnd_qualifier_t ;

/* Variables and functions */
#define  AARCH64_OPND_QLF_SP 131 
#define  AARCH64_OPND_QLF_W 130 
#define  AARCH64_OPND_QLF_WSP 129 
#define  AARCH64_OPND_QLF_X 128 
 scalar_t__ aarch64_operands ; 
 int /*<<< orphan*/  aarch64_stack_pointer_p (struct aarch64_opnd_info const*) ; 
 int /*<<< orphan*/  operand_maybe_stack_pointer (scalar_t__) ; 

__attribute__((used)) static inline int
operand_also_qualified_p (const struct aarch64_opnd_info *operand,
			  aarch64_opnd_qualifier_t target)
{
  switch (operand->qualifier)
    {
    case AARCH64_OPND_QLF_W:
      if (target == AARCH64_OPND_QLF_WSP && aarch64_stack_pointer_p (operand))
	return 1;
      break;
    case AARCH64_OPND_QLF_X:
      if (target == AARCH64_OPND_QLF_SP && aarch64_stack_pointer_p (operand))
	return 1;
      break;
    case AARCH64_OPND_QLF_WSP:
      if (target == AARCH64_OPND_QLF_W
	  && operand_maybe_stack_pointer (aarch64_operands + operand->type))
	return 1;
      break;
    case AARCH64_OPND_QLF_SP:
      if (target == AARCH64_OPND_QLF_X
	  && operand_maybe_stack_pointer (aarch64_operands + operand->type))
	return 1;
      break;
    default:
      break;
    }

  return 0;
}