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
 scalar_t__ HIHALF (scalar_t__) ; 
 int /*<<< orphan*/  LOHALF (scalar_t__) ; 
 scalar_t__ MAX_DIGIT ; 
 scalar_t__ TOHIGH (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spMultSub(DIGIT_T* uu, DIGIT_T qhat, DIGIT_T v1, DIGIT_T v0)
{
  /* Compute uu = uu - q(v1v0)
     where uu = u3u2u1u0, u3 = 0
     and u_n, v_n are all half-digits
     even though v1, v2 are passed as full digits. */
  DIGIT_T p0;
  DIGIT_T p1;
  DIGIT_T t;

  p0 = qhat * v0;
  p1 = qhat * v1;
  t = p0 + TOHIGH(LOHALF(p1));
  uu[0] -= t;
  if (uu[0] > MAX_DIGIT - t)
  {
    uu[1]--; /* Borrow */
  }
  uu[1] -= HIHALF(p1);
}