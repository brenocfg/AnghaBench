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
typedef  int /*<<< orphan*/  rk_state ;
typedef  scalar_t__ rk_error ;

/* Variables and functions */
 scalar_t__ rk_devfill (void*,size_t,int) ; 
 int /*<<< orphan*/  rk_fill (void*,size_t,int /*<<< orphan*/ *) ; 

rk_error rk_altfill(void *buffer, size_t size, int strong, rk_state *state) {
  rk_error err;

  err = rk_devfill(buffer, size, strong);
  if (err) {
    rk_fill(buffer, size, state);
  }
  return err;
}