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

__attribute__((used)) static DIGIT_T
mpAdd(DIGIT_T* w, DIGIT_T* u, DIGIT_T* v, unsigned int ndigits)
{
  /* Calculates w = u + v
     where w, u, v are multiprecision integers of ndigits each
     Returns carry if overflow. Carry = 0 or 1.

     Ref: Knuth Vol 2 Ch 4.3.1 p 266 Algorithm A. */
  DIGIT_T k;
  unsigned int j;

  /* Step A1. Initialise */
  k = 0;
  for (j = 0; j < ndigits; j++)
  {
    /* Step A2. Add digits w_j = (u_j + v_j + k)
       Set k = 1 if carry (overflow) occurs */
    w[j] = u[j] + k;
    if (w[j] < k)
    {
      k = 1;
    }
    else
    {
      k = 0;
    }
    w[j] += v[j];
    if (w[j] < v[j])
    {
      k++;
    }
  } /* Step A3. Loop on j */
  return k; /* w_n = k */
}