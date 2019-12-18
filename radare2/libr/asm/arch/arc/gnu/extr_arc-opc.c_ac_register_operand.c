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
ac_register_operand (const struct arc_operand *op)
{
  switch (op->fmt)
    {
      case 'a':
      case 'b':
      case 'c':
      case 'A':
      case 'B':
      case '#':
      case 'C':
      case 'U':
      case 'g':
      case 'G':
      case 'r':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '!':
        return 1;
    }
    return 0;
}