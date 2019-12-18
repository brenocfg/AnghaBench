#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int children_num; } ;
typedef  TYPE_1__ mpc_ast_t ;

/* Variables and functions */
 int /*<<< orphan*/  mpc_ast_add_child (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* mpc_ast_new (char*,char*) ; 

mpc_ast_t *mpc_ast_add_root(mpc_ast_t *a) {

  mpc_ast_t *r;

  if (!a) { return a; }
  if (a->children_num == 0) { return a; }
  if (a->children_num == 1) { return a; }

  r = mpc_ast_new(">", "");
  mpc_ast_add_child(r, a);
  return r;
}