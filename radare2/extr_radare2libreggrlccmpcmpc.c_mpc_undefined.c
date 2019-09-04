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
struct TYPE_4__ {int /*<<< orphan*/ * name; int /*<<< orphan*/  type; scalar_t__ retained; } ;
typedef  TYPE_1__ mpc_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPC_TYPE_UNDEFINED ; 
 TYPE_1__* calloc (int,int) ; 

__attribute__((used)) static mpc_parser_t *mpc_undefined(void) {
  mpc_parser_t *p = calloc(1, sizeof(mpc_parser_t));
  p->retained = 0;
  p->type = MPC_TYPE_UNDEFINED;
  p->name = NULL;
  return p;
}