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
struct TYPE_7__ {int /*<<< orphan*/  f; TYPE_3__* x; } ;
struct TYPE_8__ {TYPE_1__ repeat; } ;
struct TYPE_9__ {TYPE_2__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ mpc_parser_t ;
typedef  int /*<<< orphan*/  mpc_fold_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPC_TYPE_MANY ; 
 TYPE_3__* mpc_undefined () ; 

mpc_parser_t *mpc_many(mpc_fold_t f, mpc_parser_t *a) {
  mpc_parser_t *p = mpc_undefined();
  p->type = MPC_TYPE_MANY;
  p->data.repeat.x = a;
  p->data.repeat.f = f;
  return p;
}