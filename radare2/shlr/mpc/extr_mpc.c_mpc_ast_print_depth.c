#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ col; scalar_t__ row; } ;
struct TYPE_5__ {char* tag; int children_num; struct TYPE_5__** children; int /*<<< orphan*/  contents; TYPE_1__ state; } ;
typedef  TYPE_2__ mpc_ast_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpc_ast_print_depth(mpc_ast_t *a, int d, FILE *fp) {
  
  int i;
  
  if (!a) {
    fprintf(fp, "NULL\n");
    return;
  }
  
  for (i = 0; i < d; i++) { fprintf(fp, "  "); }
  
  if (strlen(a->contents)) {
    fprintf(fp, "%s:%lu:%lu '%s'\n", a->tag, 
      (long unsigned int)(a->state.row+1),
      (long unsigned int)(a->state.col+1),
      a->contents);
  } else {
    fprintf(fp, "%s \n", a->tag);
  }
  
  for (i = 0; i < a->children_num; i++) {
    mpc_ast_print_depth(a->children[i], d+1, fp);
  }
  
}