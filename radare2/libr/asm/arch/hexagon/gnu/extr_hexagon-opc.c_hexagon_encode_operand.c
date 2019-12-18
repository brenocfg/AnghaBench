#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ptrdiff_t ;
struct TYPE_5__ {int flags; char enc_letter; int shift_count; unsigned int bits; char* fmt; } ;
typedef  TYPE_1__ hexagon_operand ;
struct TYPE_6__ {char* enc; int attributes; } ;
typedef  TYPE_2__ hexagon_opcode ;
typedef  int hexagon_insn ;

/* Variables and functions */
#define  EXTENDABLE_LOWER_CASE_IMMEDIATE 129 
#define  EXTENDABLE_UPPER_CASE_IMMEDIATE 128 
 int FALSE ; 
 long HEXAGON_HI16 (unsigned long) ; 
 long HEXAGON_LO16 (unsigned long) ; 
 int HEXAGON_OPERAND_IS_HI16 ; 
 int HEXAGON_OPERAND_IS_LO16 ; 
 int HEXAGON_OPERAND_IS_NEGATIVE ; 
 int HEXAGON_OPERAND_IS_PAIR ; 
 int HEXAGON_OPERAND_IS_SIGNED ; 
 int HEXAGON_OPERAND_IS_SUBSET ; 
 long HEXAGON_SUBREGS_TO (long,int) ; 
 int /*<<< orphan*/  ISSPACE (char) ; 
 char TOLOWER (char) ; 
 char TOUPPER (char) ; 
 int TRUE ; 
 long hexagon_extend (long*,unsigned int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,...) ; 
 size_t strlen (char*) ; 

int
hexagon_encode_operand
(const hexagon_operand *operand, hexagon_insn *insn,
 const hexagon_opcode *opcode, long avalue, long *xvalue, int is_x, int is_rel,
 char **errmsg)
{
  char enc_letter;
  int shift_count = 0;
  int num_bits = 0;
  size_t len = strlen (opcode->enc);
  unsigned bits;
  long smin, smax;
  unsigned long umin, umax;
  long xer, xed;
  union
    {
      long s;
      unsigned long u;
    } value;
  int is_s;
  ptrdiff_t i;
  static char buf [500];

  value.s = avalue;

  is_x = is_x && xvalue;
  is_s = (operand->flags & HEXAGON_OPERAND_IS_SIGNED);

  enc_letter = operand->enc_letter;

  /* TODO: there are issues with this... */
  if (FALSE && is_rel)
    switch (opcode->attributes
            & (EXTENDABLE_LOWER_CASE_IMMEDIATE | EXTENDABLE_UPPER_CASE_IMMEDIATE))
      {
      case EXTENDABLE_LOWER_CASE_IMMEDIATE:
        enc_letter = TOLOWER (enc_letter);
        break;

      case EXTENDABLE_UPPER_CASE_IMMEDIATE:
        enc_letter = TOUPPER (enc_letter);
        break;
      }

  if (operand->shift_count)
    {
      /* Make sure the low bits are zero */
      if (value.s & (~(~0L << operand->shift_count)))
        {
          if (errmsg)
            {
              sprintf (buf, "low %d bits of immediate %ld must be zero",
                       operand->shift_count, value.s);
              *errmsg = buf;
            }
          return FALSE;
        }
    }

  if (operand->flags & HEXAGON_OPERAND_IS_LO16)
    value.s = HEXAGON_LO16 (value.u);
  else if (operand->flags & HEXAGON_OPERAND_IS_HI16)
    value.s = HEXAGON_HI16 (value.u);
  else if (operand->flags & HEXAGON_OPERAND_IS_SUBSET)
    value.s = HEXAGON_SUBREGS_TO (value.s, operand->flags & HEXAGON_OPERAND_IS_PAIR);

  /* Make sure the value is within the proper range
     Must include the shift count */
  bits = operand->bits + operand->shift_count;
  smax = ~(~0L << (bits - 1));
  smin =  (~0L << (bits - 1)) + ((operand->flags & HEXAGON_OPERAND_IS_NEGATIVE)? 1: 0);
  umax = ~(~0UL << bits);
  umin = 0UL;

  xed = value.s;
  xer = hexagon_extend (&xed, bits, is_s);

  if (is_x)
    {
      is_s = (xed < 0);

      *xvalue = xer;
      value.s = xed;
    }

  /* Check if the operand fits. */
  if (is_s)
    {
      if (value.s < smin || (smax > 0 && value.s > smax))
	{
	  if (errmsg)
	    {
	      sprintf (buf, "value %ld out of range: %ld-%ld", value.s, smin, smax);
	      *errmsg = buf;
	    }
	  return FALSE;
	}
    }
  else
    {
      if (value.u < umin || (umax > 0 && value.u > umax))
	{
	  if (errmsg)
	    {
	      sprintf (buf, "value %lu out of range: %lu-%lu", value.u, umin, umax);
	      *errmsg = buf;
	    }
	  return FALSE;
	}
    }

  /* In the presence of an extender, the value is not shifted. */
  if (!is_x)
    value.s >>= operand->shift_count;

  /* Read the encoding string backwards and put a bit in each time. */
  for (i = len - 1; i >= 0; i--)
    if (!ISSPACE (opcode->enc [i]))
      {
        if (opcode->enc [i] == enc_letter)
          {
            // Clear the bit
            (*insn) &= ~(1 << shift_count);
            // Insert the new bit
            (*insn) |= (value.s & 1) << shift_count;
            value.s >>= 1;
            num_bits++;
          }
        shift_count++;
      }

  /* Make sure we encode the expected number of bits */
  if (num_bits != operand->bits)
    {
      if (errmsg)
        {
          sprintf (buf, "did not encode expected number of bits: %d != %d\n"
                   "enc = %s\n  operand = %s",
                   num_bits, operand->bits, opcode->enc, operand->fmt);
          *errmsg = buf;
        }
      return FALSE;
    }

  return TRUE;
}