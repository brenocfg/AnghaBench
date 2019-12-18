#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ **** mpca_stmt_t ;
typedef  int /*<<< orphan*/ ***** mpc_val_t ;

/* Variables and functions */
 int /*<<< orphan*/ ****** malloc (int) ; 

__attribute__((used)) static mpc_val_t *mpca_stmt_fold(int n, mpc_val_t **xs) {
  
  int i;
  mpca_stmt_t **stmts = malloc(sizeof(mpca_stmt_t*) * (n+1));
  
  for (i = 0; i < n; i++) {
    stmts[i] = xs[i];
  }
  stmts[n] = NULL;  
  
  return stmts;
}