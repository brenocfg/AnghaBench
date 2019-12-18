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
 int /*<<< orphan*/  spMultiply (scalar_t__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
mpMultiply(DIGIT_T* w, DIGIT_T* u, DIGIT_T* v, unsigned int ndigits)
{
  /* Computes product w = u * v
     where u, v are multiprecision integers of ndigits each
     and w is a multiprecision integer of 2*ndigits
     Ref: Knuth Vol 2 Ch 4.3.1 p 268 Algorithm M. */
  DIGIT_T k;
  DIGIT_T t[2];
  unsigned int i;
  unsigned int j;
  unsigned int m;
  unsigned int n;

  n = ndigits;
  m = n;
  /* Step M1. Initialise */
  for (i = 0; i < 2 * m; i++)
  {
    w[i] = 0;
  }
  for (j = 0; j < n; j++)
  {
    /* Step M2. Zero multiplier? */
    if (v[j] == 0)
    {
      w[j + m] = 0;
    }
    else
    {
      /* Step M3. Initialise i */
      k = 0;
      for (i = 0; i < m; i++)
      {
        /* Step M4. Multiply and add */
        /* t = u_i * v_j + w_(i+j) + k */
        spMultiply(t, u[i], v[j]);
        t[0] += k;
        if (t[0] < k)
        {
          t[1]++;
        }
        t[0] += w[i + j];
        if (t[0] < w[i+j])
        {
          t[1]++;
        }
        w[i + j] = t[0];
        k = t[1];
      }
      /* Step M5. Loop on i, set w_(j+m) = k */
      w[j + m] = k;
    }
  } /* Step M6. Loop on j */
  return 0;
}