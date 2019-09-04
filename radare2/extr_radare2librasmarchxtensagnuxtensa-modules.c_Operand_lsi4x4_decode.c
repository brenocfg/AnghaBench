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
Operand_lsi4x4_decode (uint32 *valp)
{
  unsigned lsi4x4_0, r_0;
  r_0 = *valp & 0xf;
  lsi4x4_0 = r_0 << 2;
  *valp = lsi4x4_0;
  return 0;
}