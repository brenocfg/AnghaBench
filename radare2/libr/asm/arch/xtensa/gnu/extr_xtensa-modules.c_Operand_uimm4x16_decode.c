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
typedef  int uint32 ;

/* Variables and functions */

__attribute__((used)) static int
Operand_uimm4x16_decode (uint32 *valp)
{
  unsigned uimm4x16_0, op2_0;
  op2_0 = *valp & 0xf;
  uimm4x16_0 = op2_0 << 4;
  *valp = uimm4x16_0;
  return 0;
}