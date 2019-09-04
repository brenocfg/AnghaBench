#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ mpc_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPC_TYPE_UNDEFINED ; 
 int /*<<< orphan*/  mpc_undefine_unretained (TYPE_1__*,int) ; 

mpc_parser_t *mpc_undefine(mpc_parser_t *p) {
  mpc_undefine_unretained(p, 1);
  p->type = MPC_TYPE_UNDEFINED;
  return p;
}