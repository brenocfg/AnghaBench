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
 int HIHALF (int) ; 
 int LOHALF (int) ; 
 int TOHIGH (int) ; 

__attribute__((used)) static int
spMultiply(DIGIT_T* p, DIGIT_T x, DIGIT_T y)
{ /* Computes p = x * y */
  /* Ref: Arbitrary Precision Computation
     http://numbers.computation.free.fr/Constants/constants.html

         high    p1                p0     low
        +--------+--------+--------+--------+
        |      x1*y1      |      x0*y0      |
        +--------+--------+--------+--------+
               +-+--------+--------+
               |1| (x0*y1 + x1*y1) |
               +-+--------+--------+
                ^carry from adding (x0*y1+x1*y1) together
                        +-+
                        |1|< carry from adding LOHALF t
                        +-+  to high half of p0 */
  DIGIT_T x0;
  DIGIT_T y0;
  DIGIT_T x1;
  DIGIT_T y1;
  DIGIT_T t;
  DIGIT_T u;
  DIGIT_T carry;

  /* Split each x,y into two halves
     x = x0 + B * x1
     y = y0 + B * y1
     where B = 2^16, half the digit size
     Product is
        xy = x0y0 + B(x0y1 + x1y0) + B^2(x1y1) */

  x0 = LOHALF(x);
  x1 = HIHALF(x);
  y0 = LOHALF(y);
  y1 = HIHALF(y);

  /* Calc low part - no carry */
  p[0] = x0 * y0;

  /* Calc middle part */
  t = x0 * y1;
  u = x1 * y0;
  t += u;
  if (t < u)
  {
    carry = 1;
  }
  else
  {
    carry = 0;
  }
  /* This carry will go to high half of p[1]
     + high half of t into low half of p[1] */
  carry = TOHIGH(carry) + HIHALF(t);

  /* Add low half of t to high half of p[0] */
  t = TOHIGH(t);
  p[0] += t;
  if (p[0] < t)
  {
    carry++;
  }

  p[1] = x1 * y1;
  p[1] += carry;

  return 0;
}