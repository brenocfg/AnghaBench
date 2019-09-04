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
struct arc_operand {int fmt; } ;

/* Variables and functions */

int
ac_constant_operand (const struct arc_operand *op)
{
  switch (op->fmt)
    {
    case '@': /* This is valid only for A700 . The checks in the instruction patterns would take care of other checks.*/

      case 'u':
      case 'K':
      case 'L':
      case 'o':
      case 'e':
      case 'E':
      case 'j':
      case 'J':
      case 'k':
      case 'l':
      case 'm':
      case 'M':
      case 'O':
      case 'R':
	/* Operands for the Aurora SIMD ISA*/
      case '?':
      case '\14':
      case '\20':
      case '\21':
      case '\22':
      case '\23':
      case '\24':
      case '\25':

        return 1;
    }
    return 0;
}