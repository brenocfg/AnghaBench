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
typedef  scalar_t__ DIGIT_T ;

/* Variables and functions */

__attribute__((used)) static unsigned int
mpSizeof(DIGIT_T* a, unsigned int ndigits)
{  /* Returns size of significant digits in a */
  while (ndigits--)
  {
    if (a[ndigits] != 0)
    {
      return (++ndigits);
    }
  }
  return 0;
}