#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpc_val_t ;
struct TYPE_6__ {int /*<<< orphan*/ * x; } ;
struct TYPE_7__ {TYPE_1__ lift; } ;
struct TYPE_8__ {TYPE_2__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ mpc_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPC_TYPE_LIFT_VAL ; 
 TYPE_3__* mpc_undefined () ; 

mpc_parser_t *mpc_lift_val(mpc_val_t *x) {
  mpc_parser_t *p = mpc_undefined();
  p->type = MPC_TYPE_LIFT_VAL;
  p->data.lift.x = x;
  return p;
}