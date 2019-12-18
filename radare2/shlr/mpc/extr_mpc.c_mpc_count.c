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
struct TYPE_8__ {int n; int /*<<< orphan*/  dx; TYPE_3__* x; int /*<<< orphan*/  f; } ;
struct TYPE_7__ {TYPE_2__ repeat; } ;
struct TYPE_9__ {TYPE_1__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ mpc_parser_t ;
typedef  int /*<<< orphan*/  mpc_fold_t ;
typedef  int /*<<< orphan*/  mpc_dtor_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPC_TYPE_COUNT ; 
 TYPE_3__* mpc_undefined () ; 

mpc_parser_t *mpc_count(int n, mpc_fold_t f, mpc_parser_t *a, mpc_dtor_t da) {
  mpc_parser_t *p = mpc_undefined();
  p->type = MPC_TYPE_COUNT;
  p->data.repeat.n = n;
  p->data.repeat.f = f;
  p->data.repeat.x = a;
  p->data.repeat.dx = da;
  return p;
}