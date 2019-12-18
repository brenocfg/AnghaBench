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

__attribute__((used)) static int
mpCompare(DIGIT_T* a, DIGIT_T* b, unsigned int ndigits)
{
  /* Returns sign of (a - b) */
  if (ndigits == 0)
  {
    return 0;
  }
  while (ndigits--)
  {
    if (a[ndigits] > b[ndigits])
    {
      return 1; /* GT */
    }
    if (a[ndigits] < b[ndigits])
    {
      return -1; /* LT */
    }
  }
  return 0; /* EQ */
}