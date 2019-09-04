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
Operand_simm8x256_decode (uint32 *valp)
{
  unsigned simm8x256_0, imm8_0;
  imm8_0 = *valp & 0xff;
  simm8x256_0 = (((int) imm8_0 << 24) >> 24) << 8;
  *valp = simm8x256_0;
  return 0;
}