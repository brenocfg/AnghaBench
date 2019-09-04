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
 int HEXAGON_OPERAND_IS_REGISTER ; 
 scalar_t__ hexagon_encode_operand (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  hexagon_gp_regs ; 
 int /*<<< orphan*/  hexagon_gp_regs_count ; 
 int hexagon_reg_num (int /*<<< orphan*/  const*,char**,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char) ; 

char *
hexagon_parse_reg8
(const hexagon_operand *operand, hexagon_insn *insn, const hexagon_opcode *opcode,
 char *input, long *val, int *flag, char **errmsg)
{
  int reg;

  reg = hexagon_reg_num (operand, &input, 'r', hexagon_gp_regs, hexagon_gp_regs_count, NULL, '\0');
  if (reg < 0)
    return (NULL);

  if ((reg > 3) && (reg < 16 || reg > 19))
    return (NULL);

  if (hexagon_encode_operand
        (operand, insn, opcode, reg, NULL, FALSE, FALSE, errmsg))
    {
      if (flag)
        *flag = HEXAGON_OPERAND_IS_REGISTER;

      *val = reg;
      return (input);
    }

  return (NULL);
}