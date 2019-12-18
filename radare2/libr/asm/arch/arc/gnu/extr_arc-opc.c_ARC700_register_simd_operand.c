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

/* Variables and functions */

int
ARC700_register_simd_operand (char fmt)
{
  switch (fmt)
    {
    case '*':
    case '(':
    case ')':
      return 1; /*If the operand belongs to  the Vector register(Vrxx) set*/
    case '<':
    case '>':
      return 2; /*If the operand belongs to the DMA registers (DRxx) set*/
    case '\13':
    case '{':
    case '}':
      return 3; /*If the operand belongs to the Scalar register (Ixx) set*/
    case '\15':
    case '\16':
    case '\17':
      return 4; /*If the operand belongs to the Scalar register (Kxx) set*/
    }
  return 0;
}