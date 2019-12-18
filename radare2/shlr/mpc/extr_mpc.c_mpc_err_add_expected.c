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
 int /*<<< orphan*/  mpc_malloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * mpc_realloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void mpc_err_add_expected(mpc_input_t *i, mpc_err_t *x, char *expected) {
  (void)i;
  x->expected_num++;
  x->expected = mpc_realloc(i, x->expected, sizeof(char*) * x->expected_num);
  x->expected[x->expected_num-1] = mpc_malloc(i, strlen(expected) + 1);
  strcpy(x->expected[x->expected_num-1], expected);
}