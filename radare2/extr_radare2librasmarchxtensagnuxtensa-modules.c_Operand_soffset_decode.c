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
Operand_soffset_decode (uint32 *valp)
{
  unsigned soffset_0, offset_0;
  offset_0 = *valp & 0x3ffff;
  soffset_0 = 0x4 + (((int) offset_0 << 14) >> 14);
  *valp = soffset_0;
  return 0;
}