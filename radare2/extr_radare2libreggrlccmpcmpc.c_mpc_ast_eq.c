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
struct TYPE_4__ {int children_num; struct TYPE_4__** children; int /*<<< orphan*/  contents; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ mpc_ast_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mpc_ast_eq(mpc_ast_t *a, mpc_ast_t *b) {
  
  int i;

  if (strcmp(a->tag, b->tag) != 0) { return 0; }
  if (strcmp(a->contents, b->contents) != 0) { return 0; }
  if (a->children_num != b->children_num) { return 0; }
  
  for (i = 0; i < a->children_num; i++) {
    if (!mpc_ast_eq(a->children[i], b->children[i])) { return 0; }
  }
  
  return 1;
}