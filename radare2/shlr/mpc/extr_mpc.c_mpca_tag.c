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
typedef  int /*<<< orphan*/  mpc_parser_t ;
typedef  int /*<<< orphan*/  mpc_apply_to_t ;

/* Variables and functions */
 int /*<<< orphan*/ * mpc_apply_to (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ mpc_ast_tag ; 

mpc_parser_t *mpca_tag(mpc_parser_t *a, const char *t) {
  return mpc_apply_to(a, (mpc_apply_to_t)mpc_ast_tag, (void*)t);
}