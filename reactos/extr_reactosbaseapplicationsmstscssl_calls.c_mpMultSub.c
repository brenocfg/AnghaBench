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
 scalar_t__ MAX_DIGIT ; 
 int /*<<< orphan*/  spMultiply (scalar_t__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static DIGIT_T
mpMultSub(DIGIT_T wn, DIGIT_T* w, DIGIT_T* v, DIGIT_T q, unsigned int n)
{ /* Compute w = w - qv
     where w = (WnW[n-1]...W[0])
     return modified Wn. */
  DIGIT_T k;
  DIGIT_T t[2];
  unsigned int i;

  if (q == 0) /* No change */
  {
    return wn;
  }
  k = 0;
  for (i = 0; i < n; i++)
  {
    spMultiply(t, q, v[i]);
    w[i] -= k;
    if (w[i] > MAX_DIGIT - k)
    {
      k = 1;
    }
    else
    {
      k = 0;
    }
    w[i] -= t[0];
    if (w[i] > MAX_DIGIT - t[0])
    {
      k++;
    }
    k += t[1];
  }
  /* Cope with Wn not stored in array w[0..n-1] */
  wn -= k;
  return wn;
}