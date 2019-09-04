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
typedef  int /*<<< orphan*/  mpc_input_t ;
typedef  int /*<<< orphan*/ * (* mpc_apply_to_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int /*<<< orphan*/  mpc_export (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static mpc_val_t *mpc_parse_apply_to(mpc_input_t *i, mpc_apply_to_t f, mpc_val_t *x, mpc_val_t *d) {
  return f(mpc_export(i, x), d);
}