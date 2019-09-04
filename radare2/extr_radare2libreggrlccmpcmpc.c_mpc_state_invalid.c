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
struct TYPE_3__ {int pos; int row; int col; } ;
typedef  TYPE_1__ mpc_state_t ;

/* Variables and functions */

__attribute__((used)) static mpc_state_t mpc_state_invalid(void) {
  mpc_state_t s;
  s.pos = -1;
  s.row = -1;
  s.col = -1;
  return s;
}