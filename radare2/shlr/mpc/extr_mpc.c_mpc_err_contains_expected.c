#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpc_input_t ;
struct TYPE_3__ {int expected_num; int /*<<< orphan*/ * expected; } ;
typedef  TYPE_1__ mpc_err_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mpc_err_contains_expected(mpc_input_t *i, mpc_err_t *x, char *expected) {
  int j;
  (void)i;
  for (j = 0; j < x->expected_num; j++) {
    if (strcmp(x->expected[j], expected) == 0) { return 1; }
  }
  return 0;
}