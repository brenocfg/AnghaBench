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
typedef  int /*<<< orphan*/  mpc_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/ * mpc_pass () ; 
 int /*<<< orphan*/ * mpca_and (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static mpc_val_t *mpcaf_grammar_and(int n, mpc_val_t **xs) {
  int i;
  mpc_parser_t *p = mpc_pass();  
  for (i = 0; i < n; i++) {
    if (xs[i] != NULL) { p = mpca_and(2, p, xs[i]); }
  }
  return p;
}