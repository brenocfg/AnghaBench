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
struct TYPE_7__ {int children_num; struct TYPE_7__** children; } ;
typedef  TYPE_1__ mpc_ast_t ;

/* Variables and functions */
 TYPE_1__** realloc (TYPE_1__**,int) ; 

mpc_ast_t *mpc_ast_add_child(mpc_ast_t *r, mpc_ast_t *a) {
  r->children_num++;
  r->children = realloc(r->children, sizeof(mpc_ast_t*) * r->children_num);
  r->children[r->children_num-1] = a;
  return r;
}