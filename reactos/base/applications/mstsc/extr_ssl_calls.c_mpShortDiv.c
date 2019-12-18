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
 int HIBITMASK ; 
 int mpShiftLeft (int*,int*,unsigned int,unsigned int) ; 
 int spDivide (int*,int*,int*,int) ; 

__attribute__((used)) static DIGIT_T
mpShortDiv(DIGIT_T* q, DIGIT_T* u, DIGIT_T v, unsigned int ndigits)
{
  /* Calculates quotient q = u div v
     Returns remainder r = u mod v
     where q, u are multiprecision integers of ndigits each
     and d, v are single precision digits.

     Makes no assumptions about normalisation.

     Ref: Knuth Vol 2 Ch 4.3.1 Exercise 16 p625 */
  unsigned int j;
  unsigned int shift;
  DIGIT_T t[2];
  DIGIT_T r;
  DIGIT_T bitmask;
  DIGIT_T overflow;
  DIGIT_T* uu;

  if (ndigits == 0)
  {
    return 0;
  }
  if (v == 0)
  {
    return 0; /* Divide by zero error */
  }
  /* Normalise first */
  /* Requires high bit of V
     to be set, so find most signif. bit then shift left,
     i.e. d = 2^shift, u' = u * d, v' = v * d. */
  bitmask = HIBITMASK;
  for (shift = 0; shift < BITS_PER_DIGIT; shift++)
  {
    if (v & bitmask)
    {
      break;
    }
    bitmask >>= 1;
  }
  v <<= shift;
  overflow = mpShiftLeft(q, u, shift, ndigits);
  uu = q;
  /* Step S1 - modified for extra digit. */
  r = overflow; /* New digit Un */
  j = ndigits;
  while (j--)
  {
    /* Step S2. */
    t[1] = r;
    t[0] = uu[j];
    overflow = spDivide(&q[j], &r, t, v);
  }
  /* Unnormalise */
  r >>= shift;
  return r;
}