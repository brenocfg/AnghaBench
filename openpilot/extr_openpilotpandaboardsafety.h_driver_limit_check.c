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
struct sample_t {int const max; int const min; } ;

/* Variables and functions */
 int const max (int,int const) ; 
 int const min (int,int const) ; 

int driver_limit_check(int val, int val_last, struct sample_t *val_driver,
  const int MAX, const int MAX_RATE_UP, const int MAX_RATE_DOWN,
  const int MAX_ALLOWANCE, const int DRIVER_FACTOR) {

  int highest_allowed = max(val_last, 0) + MAX_RATE_UP;
  int lowest_allowed = min(val_last, 0) - MAX_RATE_UP;

  int driver_max_limit = MAX + (MAX_ALLOWANCE + val_driver->max) * DRIVER_FACTOR;
  int driver_min_limit = -MAX + (-MAX_ALLOWANCE + val_driver->min) * DRIVER_FACTOR;

  // if we've exceeded the applied torque, we must start moving toward 0
  highest_allowed = min(highest_allowed, max(val_last - MAX_RATE_DOWN,
                                             max(driver_max_limit, 0)));
  lowest_allowed = max(lowest_allowed, min(val_last + MAX_RATE_DOWN,
                                           min(driver_min_limit, 0)));

  // check for violation
  return (val < lowest_allowed) || (val > highest_allowed);
}