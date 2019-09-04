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
typedef  unsigned int uint32 ;

/* Variables and functions */

__attribute__((used)) static int
Operand_ai4const_encode (uint32 *valp)
{
  unsigned t_0, ai4const_0;
  ai4const_0 = *valp;
  switch (ai4const_0)
    {
    case 0xffffffff: t_0 = 0; break;
    case 0x1: t_0 = 0x1; break;
    case 0x2: t_0 = 0x2; break;
    case 0x3: t_0 = 0x3; break;
    case 0x4: t_0 = 0x4; break;
    case 0x5: t_0 = 0x5; break;
    case 0x6: t_0 = 0x6; break;
    case 0x7: t_0 = 0x7; break;
    case 0x8: t_0 = 0x8; break;
    case 0x9: t_0 = 0x9; break;
    case 0xa: t_0 = 0xa; break;
    case 0xb: t_0 = 0xb; break;
    case 0xc: t_0 = 0xc; break;
    case 0xd: t_0 = 0xd; break;
    case 0xe: t_0 = 0xe; break;
    default: t_0 = 0xf; break;
    }
  *valp = t_0;
  return 0;
}