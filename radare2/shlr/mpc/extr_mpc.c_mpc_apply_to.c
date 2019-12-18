#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* d; int /*<<< orphan*/  f; TYPE_3__* x; } ;
struct TYPE_8__ {TYPE_1__ apply_to; } ;
struct TYPE_9__ {TYPE_2__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ mpc_parser_t ;
typedef  int /*<<< orphan*/  mpc_apply_to_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPC_TYPE_APPLY_TO ; 
 TYPE_3__* mpc_undefined () ; 

mpc_parser_t *mpc_apply_to(mpc_parser_t *a, mpc_apply_to_t f, void *x) {
  mpc_parser_t *p = mpc_undefined();
  p->type = MPC_TYPE_APPLY_TO;
  p->data.apply_to.x = a;
  p->data.apply_to.f = f;
  p->data.apply_to.d = x;
  return p;
}