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
struct TYPE_3__ {char enc_letter; unsigned int bits; int flags; int shift_count; } ;
typedef  TYPE_1__ hexagon_operand ;
typedef  int hexagon_insn ;
typedef  scalar_t__ bfd_vma ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ HEXAGON_IS16BITS (int) ; 
 int HEXAGON_OPERAND_IS_PAIR ; 
 int HEXAGON_OPERAND_IS_SIGNED ; 
 int HEXAGON_OPERAND_IS_SUBSET ; 
 int HEXAGON_OPERAND_PC_RELATIVE ; 
 int HEXAGON_SUBREGS_FROM (int,int) ; 
 int /*<<< orphan*/  ISSPACE (char) ; 
 int TRUE ; 
 int /*<<< orphan*/  sprintf (char*,char*,char,char*,unsigned int,unsigned int) ; 

int
hexagon_extract_operand
(const hexagon_operand *operand, hexagon_insn insn,
 bfd_vma addr, char *enc, int *return_value,
 char **errmsg)
{
  int value = 0;
  char enc_letter = operand->enc_letter;
  char *enc_ptr = enc;
  unsigned int bits_found;
  hexagon_insn mask;

  if (HEXAGON_IS16BITS(insn))
    mask = 1 << 15;
  else
    mask = 1 << 31;

  /* Grab the bits from the instruction */
  bits_found = 0;
  while (*enc_ptr)
    {
      char ch = *enc_ptr++;

      if (!ISSPACE(ch))
        {
          if (ch == enc_letter)
            {
              value = (value << 1) + ((insn & mask)? 1: 0);
              bits_found++;
            }
          mask >>= 1;
        }
    }

  /* Check that we got the right number of bits */
  if (bits_found != operand->bits)
    {
      if (errmsg)
        {
          static char xx[100];

          sprintf (xx, "operand %c wrong number of bits found in %s, %d != %d",
                   operand->enc_letter, enc, bits_found, operand->bits);
          *errmsg = xx;
        }
      return FALSE;
    }

  if (operand->flags & HEXAGON_OPERAND_IS_SIGNED)
    {
      if (bits_found > 31) {
        // invalid bitshift
        return FALSE;
      }
      /* Might need to sign extend */
      if (value & (1 << (bits_found - 1)))
        {
          value <<= 32 - bits_found;
          value >>= 32 - bits_found;
        }
    }

  value <<= operand->shift_count;

  if (operand->flags & HEXAGON_OPERAND_PC_RELATIVE)
    value += addr;

  if (operand->flags & HEXAGON_OPERAND_IS_SUBSET)
    value = HEXAGON_SUBREGS_FROM (value, operand->flags & HEXAGON_OPERAND_IS_PAIR);

  *return_value = value;
  return TRUE;
}