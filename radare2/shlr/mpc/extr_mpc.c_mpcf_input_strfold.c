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

/* Variables and functions */
 int /*<<< orphan*/ * mpc_calloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mpc_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpc_realloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static mpc_val_t *mpcf_input_strfold(mpc_input_t *i, int n, mpc_val_t **xs) {
  int j;
  size_t l = 0;
  if (n == 0) { return mpc_calloc(i, 1, 1); }
  for (j = 0; j < n; j++) { l += strlen(xs[j]); }
  xs[0] = mpc_realloc(i, xs[0], l + 1);
  for (j = 1; j < n; j++) { strcat(xs[0], xs[j]); mpc_free(i, xs[j]); }
  return xs[0];
}