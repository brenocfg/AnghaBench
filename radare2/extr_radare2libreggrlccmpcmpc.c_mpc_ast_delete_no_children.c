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
struct TYPE_4__ {struct TYPE_4__* contents; struct TYPE_4__* tag; struct TYPE_4__* children; } ;
typedef  TYPE_1__ mpc_ast_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void mpc_ast_delete_no_children(mpc_ast_t *a) {
  free(a->children);
  free(a->tag);
  free(a->contents);
  free(a);
}