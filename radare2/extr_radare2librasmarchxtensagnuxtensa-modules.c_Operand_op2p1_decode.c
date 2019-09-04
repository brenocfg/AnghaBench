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
Operand_op2p1_decode (uint32 *valp)
{
  unsigned op2p1_0, op2_0;
  op2_0 = *valp & 0xf;
  op2p1_0 = op2_0 + 0x1;
  *valp = op2p1_0;
  return 0;
}