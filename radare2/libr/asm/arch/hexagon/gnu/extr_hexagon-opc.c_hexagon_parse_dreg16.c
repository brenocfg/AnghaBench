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
typedef  int /*<<< orphan*/  hexagon_operand ;
typedef  int /*<<< orphan*/  hexagon_opcode ;
typedef  int /*<<< orphan*/  hexagon_insn ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int HEXAGON_OPERAND_IS_PAIR ; 
 scalar_t__ hexagon_encode_operand (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  hexagon_gp_regs ; 
 int /*<<< orphan*/  hexagon_gp_regs_count ; 
 int hexagon_reg_num (int /*<<< orphan*/  const*,char**,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

__attribute__((used)) static char *
hexagon_parse_dreg16
(const hexagon_operand *operand, hexagon_insn *insn, const hexagon_opcode *opcode,
 char *input, long *val, int *flag, char **errmsg)
{
  int reg_odd;
  int reg_even;

  reg_odd  = hexagon_reg_num (operand, &input, 'r', hexagon_gp_regs, hexagon_gp_regs_count, NULL, '\0');
  reg_even = hexagon_reg_num (operand, &input, ':', hexagon_gp_regs, hexagon_gp_regs_count, NULL, '\0');
  if (reg_odd < 0 || reg_even < 0)
    return (NULL);

  /* Make sure the register number is odd */
  if (reg_odd % 2 != 1)
    {
      if (errmsg)
        {
            static char buf [100];
            sprintf (buf, "invalid odd register number: %d", reg_odd);
            *errmsg = buf;
        }
      return (NULL);
    }

  /* Make sure the register number is even */
  if (reg_even % 2 != 0)
    {
      if (errmsg)
        {
            static char buf [100];
            sprintf (buf, "invalid even register number: %d", reg_even);
            *errmsg = buf;
        }
      return (NULL);
    }

  /* Make sure the registers are consecutive */
  if (reg_odd != reg_even + 1)
    {
      if (errmsg)
        {
            static char buf [100];
            sprintf (buf, "registers must be consecutive: %d:%d",
                      reg_odd, reg_even);
            *errmsg = buf;
        }
      return (NULL);
    }

  if (((reg_odd  < 1 || reg_odd  > 31))
      || ((reg_even < 0 || reg_even > 30)))
    return (NULL);

  if (hexagon_encode_operand
        (operand, insn, opcode, reg_even, NULL, FALSE, FALSE, errmsg))
    {
      if (flag)
        *flag = HEXAGON_OPERAND_IS_PAIR;

      *val = reg_even;
      return (input);
    }

  return (NULL);
}