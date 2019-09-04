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
typedef  int DIGIT_T ;

/* Variables and functions */
 unsigned int BITS_PER_DIGIT ; 

__attribute__((used)) static DIGIT_T
mpShiftRight(DIGIT_T* a, DIGIT_T* b, unsigned int x, unsigned int ndigits)
{ /* Computes a = b >> x */
  unsigned int i;
  unsigned int y;
  DIGIT_T mask;
  DIGIT_T carry;
  DIGIT_T nextcarry;

  /* Check input  - NB unspecified result */
  if (x >= BITS_PER_DIGIT)
  {
    return 0;
  }
  /* Construct mask */
  mask = 0x1;
  for (i = 1; i < x; i++)
  {
    mask = (mask << 1) | mask;
  }
  if (x == 0)
  {
    mask = 0x0;
  }
  y = BITS_PER_DIGIT - x;
  carry = 0;
  i = ndigits;
  while (i--)
  {
    nextcarry = (b[i] & mask) << y;
    a[i] = b[i] >> x | carry;
    carry = nextcarry;
  }
  return carry;
}