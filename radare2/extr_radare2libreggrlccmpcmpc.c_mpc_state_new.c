#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ col; scalar_t__ row; scalar_t__ pos; } ;
typedef  TYPE_1__ mpc_state_t ;

/* Variables and functions */

__attribute__((used)) static mpc_state_t mpc_state_new(void) {
  mpc_state_t s;
  s.pos = 0;
  s.row = 0;
  s.col = 0;
  return s;
}