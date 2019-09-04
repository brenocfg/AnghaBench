#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpc_state_t ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ mpc_ast_t ;

/* Variables and functions */

mpc_ast_t *mpc_ast_state(mpc_ast_t *a, mpc_state_t s) {
  if (!a) { return a; }
  a->state = s;
  return a;
}