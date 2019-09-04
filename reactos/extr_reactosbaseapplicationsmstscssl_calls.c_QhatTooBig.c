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
QhatTooBig(DIGIT_T qhat, DIGIT_T rhat, DIGIT_T vn2, DIGIT_T ujn2)
{ /* Returns true if Qhat is too big
     i.e. if (Qhat * Vn-2) > (b.Rhat + Uj+n-2) */
  DIGIT_T t[2];

  spMultiply(t, qhat, vn2);
  if (t[1] < rhat)
  {
    return 0;
  }
  else if (t[1] > rhat)
  {
    return 1;
  }
  else if (t[0] > ujn2)
  {
    return 1;
  }
  return 0;
}