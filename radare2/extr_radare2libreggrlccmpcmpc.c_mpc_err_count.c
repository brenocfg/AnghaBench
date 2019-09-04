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
typedef  int /*<<< orphan*/  mpc_input_t ;
typedef  int /*<<< orphan*/  mpc_err_t ;

/* Variables and functions */
 int /*<<< orphan*/ * mpc_err_repeat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mpc_free (int /*<<< orphan*/ *,char*) ; 
 char* mpc_malloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static mpc_err_t *mpc_err_count(mpc_input_t *i, mpc_err_t *x, int n) {
  mpc_err_t *y;
  int digits = n/10 + 1;
  char *prefix;
  prefix = mpc_malloc(i, digits + strlen(" of ") + 1);
  sprintf(prefix, "%i of ", n);
  y = mpc_err_repeat(i, x, prefix);
  mpc_free(i, prefix);
  return y;
}