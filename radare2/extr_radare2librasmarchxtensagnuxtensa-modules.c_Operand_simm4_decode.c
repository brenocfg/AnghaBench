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
Operand_simm4_decode (uint32 *valp)
{
  unsigned simm4_0, mn_0;
  mn_0 = *valp & 0xf;
  simm4_0 = ((int) mn_0 << 28) >> 28;
  *valp = simm4_0;
  return 0;
}