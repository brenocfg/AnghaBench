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

/* Variables and functions */
 int const max (int,int /*<<< orphan*/ ) ; 
 int const min (int,int /*<<< orphan*/ ) ; 

int rt_rate_limit_check(int val, int val_last, const int MAX_RT_DELTA) {

  // *** torque real time rate limit check ***
  int highest_val = max(val_last, 0) + MAX_RT_DELTA;
  int lowest_val = min(val_last, 0) - MAX_RT_DELTA;

  // check for violation
  return (val < lowest_val) || (val > highest_val);
}