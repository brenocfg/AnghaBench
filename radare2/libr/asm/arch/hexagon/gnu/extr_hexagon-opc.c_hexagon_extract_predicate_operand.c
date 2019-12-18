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
typedef  int /*<<< orphan*/  hexagon_insn ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  hexagon_dis_operand (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char**) ; 
 int /*<<< orphan*/  hexagon_extract_operand (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,char**) ; 

int
hexagon_extract_predicate_operand
(const hexagon_operand *operand, hexagon_insn insn,
 char *enc, int *return_value, char **errmsg)
{
  char reg_name [100];
  int reg_num;

  // Get the predicate register name from the instruction
  if (!hexagon_dis_operand (operand, insn, 0, 0, enc, reg_name, errmsg))
    return FALSE;

  // Get the predicate register number
  if (!hexagon_extract_operand (operand, insn, 0, enc, &reg_num, errmsg))
    return FALSE;

  *return_value = reg_num;
  return TRUE;
}