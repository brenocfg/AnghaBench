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
 int B_J ; 
 int HIBITMASK ; 
 int HIHALF (int) ; 
 int LOHALF (int) ; 
 int MAX_DIGIT ; 
 int TOHIGH (int) ; 
 int /*<<< orphan*/  spMultSub (int*,int,int,int) ; 

__attribute__((used)) static DIGIT_T
spDivide(DIGIT_T* q, DIGIT_T* r, DIGIT_T* u, DIGIT_T v)
{ /* Computes quotient q = u / v, remainder r = u mod v
     where u is a double digit
     and q, v, r are single precision digits.
     Returns high digit of quotient (max value is 1)
     Assumes normalised such that v1 >= b/2
     where b is size of HALF_DIGIT
     i.e. the most significant bit of v should be one

     In terms of half-digits in Knuth notation:
     (q2q1q0) = (u4u3u2u1u0) / (v1v0)
     (r1r0) = (u4u3u2u1u0) mod (v1v0)
     for m = 2, n = 2 where u4 = 0
     q2 is either 0 or 1.
     We set q = (q1q0) and return q2 as "overflow' */
  DIGIT_T qhat;
  DIGIT_T rhat;
  DIGIT_T t;
  DIGIT_T v0;
  DIGIT_T v1;
  DIGIT_T u0;
  DIGIT_T u1;
  DIGIT_T u2;
  DIGIT_T u3;
  DIGIT_T uu[2];
  DIGIT_T q2;

  /* Check for normalisation */
  if (!(v & HIBITMASK))
  {
    *q = *r = 0;
    return MAX_DIGIT;
  }

  /* Split up into half-digits */
  v0 = LOHALF(v);
  v1 = HIHALF(v);
  u0 = LOHALF(u[0]);
  u1 = HIHALF(u[0]);
  u2 = LOHALF(u[1]);
  u3 = HIHALF(u[1]);

  /* Do three rounds of Knuth Algorithm D Vol 2 p272 */

  /* ROUND 1. Set j = 2 and calculate q2 */
  /* Estimate qhat = (u4u3)/v1  = 0 or 1
     then set (u4u3u2) -= qhat(v1v0)
     where u4 = 0. */
  qhat = u3 / v1;
  if (qhat > 0)
  {
    rhat = u3 - qhat * v1;
    t = TOHIGH(rhat) | u2;
    if (qhat * v0 > t)
    {
      qhat--;
    }
  }
  uu[1] = 0; /* (u4) */
  uu[0] = u[1]; /* (u3u2) */
  if (qhat > 0)
  {
    /* (u4u3u2) -= qhat(v1v0) where u4 = 0 */
    spMultSub(uu, qhat, v1, v0);
    if (HIHALF(uu[1]) != 0)
    { /* Add back */
      qhat--;
      uu[0] += v;
      uu[1] = 0;
    }
  }
  q2 = qhat;
  /* ROUND 2. Set j = 1 and calculate q1 */
  /* Estimate qhat = (u3u2) / v1
     then set (u3u2u1) -= qhat(v1v0) */
  t = uu[0];
  qhat = t / v1;
  rhat = t - qhat * v1;
  /* Test on v0 */
  t = TOHIGH(rhat) | u1;
  if ((qhat == B_J) || (qhat * v0 > t))
  {
    qhat--;
    rhat += v1;
    t = TOHIGH(rhat) | u1;
    if ((rhat < B_J) && (qhat * v0 > t))
    {
      qhat--;
    }
  }
  /* Multiply and subtract
     (u3u2u1)' = (u3u2u1) - qhat(v1v0) */
  uu[1] = HIHALF(uu[0]); /* (0u3) */
  uu[0] = TOHIGH(LOHALF(uu[0])) | u1; /* (u2u1) */
  spMultSub(uu, qhat, v1, v0);
  if (HIHALF(uu[1]) != 0)
  { /* Add back */
    qhat--;
    uu[0] += v;
    uu[1] = 0;
  }
  /* q1 = qhat */
  *q = TOHIGH(qhat);
  /* ROUND 3. Set j = 0 and calculate q0 */
  /* Estimate qhat = (u2u1) / v1
     then set (u2u1u0) -= qhat(v1v0) */
  t = uu[0];
  qhat = t / v1;
  rhat = t - qhat * v1;
  /* Test on v0 */
  t = TOHIGH(rhat) | u0;
  if ((qhat == B_J) || (qhat * v0 > t))
  {
    qhat--;
    rhat += v1;
    t = TOHIGH(rhat) | u0;
    if ((rhat < B_J) && (qhat * v0 > t))
    {
      qhat--;
    }
  }
  /* Multiply and subtract
     (u2u1u0)" = (u2u1u0)' - qhat(v1v0) */
  uu[1] = HIHALF(uu[0]); /* (0u2) */
  uu[0] = TOHIGH(LOHALF(uu[0])) | u0; /* (u1u0) */
  spMultSub(uu, qhat, v1, v0);
  if (HIHALF(uu[1]) != 0)
  { /* Add back */
    qhat--;
    uu[0] += v;
    uu[1] = 0;
  }
  /* q0 = qhat */
  *q |= LOHALF(qhat);
  /* Remainder is in (u1u0) i.e. uu[0] */
  *r = uu[0];
  return q2;
}