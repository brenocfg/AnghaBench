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
struct sample_t {int max; int min; } ;

/* Variables and functions */
 int const max (int,int const) ; 
 int const min (int,int const) ; 

int dist_to_meas_check(int val, int val_last, struct sample_t *val_meas,
  const int MAX_RATE_UP, const int MAX_RATE_DOWN, const int MAX_ERROR) {

  // *** val rate limit check ***
  int highest_allowed_val = max(val_last, 0) + MAX_RATE_UP;
  int lowest_allowed_val = min(val_last, 0) - MAX_RATE_UP;

  // if we've exceeded the meas val, we must start moving toward 0
  highest_allowed_val = min(highest_allowed_val, max(val_last - MAX_RATE_DOWN, max(val_meas->max, 0) + MAX_ERROR));
  lowest_allowed_val = max(lowest_allowed_val, min(val_last + MAX_RATE_DOWN, min(val_meas->min, 0) - MAX_ERROR));

  // check for violation
  return (val < lowest_allowed_val) || (val > highest_allowed_val);
}