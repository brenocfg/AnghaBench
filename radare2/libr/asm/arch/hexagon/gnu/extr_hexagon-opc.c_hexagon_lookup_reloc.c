#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; scalar_t__ reloc_kxed; scalar_t__ reloc_type; int /*<<< orphan*/  fmt; int /*<<< orphan*/  enc_letter; } ;
typedef  TYPE_1__ hexagon_operand ;
struct TYPE_7__ {int attributes; int /*<<< orphan*/  syntax; } ;
typedef  TYPE_2__ hexagon_opcode ;
typedef  scalar_t__ bfd_reloc_code_real_type ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_NONE ; 
#define  EXTENDABLE_LOWER_CASE_IMMEDIATE 129 
#define  EXTENDABLE_UPPER_CASE_IMMEDIATE 128 
 int HEXAGON_OPERAND_IS_IMMEDIATE ; 
 int HEXAGON_OPERAND_IS_KXED ; 
 int /*<<< orphan*/  TOLOWER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOUPPER (int /*<<< orphan*/ ) ; 
 size_t hexagon_operand_count ; 
 TYPE_1__ const* hexagon_operands ; 
 int /*<<< orphan*/  strstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const hexagon_operand *
hexagon_lookup_reloc
(bfd_reloc_code_real_type reloc_type, int flags, const hexagon_opcode *opcode)
{
  bfd_reloc_code_real_type r;
  size_t i;

  if (reloc_type == BFD_RELOC_NONE || !opcode)
    return NULL;

  for (i = 0; i < hexagon_operand_count; i++)
    {
      if (flags & HEXAGON_OPERAND_IS_KXED)
        {
          if (hexagon_operands [i].flags & HEXAGON_OPERAND_IS_IMMEDIATE)
            switch (opcode->attributes
                    & (EXTENDABLE_LOWER_CASE_IMMEDIATE
                       | EXTENDABLE_UPPER_CASE_IMMEDIATE))
              {
              case EXTENDABLE_LOWER_CASE_IMMEDIATE:
                if (hexagon_operands [i].enc_letter
                    != TOLOWER (hexagon_operands [i].enc_letter)
                    || !strstr (opcode->syntax, hexagon_operands [i].fmt))
                  continue;

                break;

              case EXTENDABLE_UPPER_CASE_IMMEDIATE:
                if (hexagon_operands [i].enc_letter
                    != TOUPPER (hexagon_operands [i].enc_letter)
                    || !strstr (opcode->syntax, hexagon_operands [i].fmt))
                  continue;

                break;
              }

          r = hexagon_operands [i].reloc_kxed;
        }
      else
        r = hexagon_operands [i].reloc_type;

      if (r == reloc_type)
        return (hexagon_operands + i);
    }

  return NULL;
}