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
typedef  int /*<<< orphan*/  mpc_val_t ;
typedef  int /*<<< orphan*/  mpc_state_t ;
typedef  int /*<<< orphan*/  mpc_ast_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpc_ast_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

mpc_val_t *mpcf_state_ast(int n, mpc_val_t **xs) {
  mpc_state_t *s = ((mpc_state_t**)xs)[0];
  mpc_ast_t *a = ((mpc_ast_t**)xs)[1];
  (void)n;
  a = mpc_ast_state(a, *s);
  free(s);
  return a;
}