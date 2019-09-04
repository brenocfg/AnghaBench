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

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpc_count (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/ * mpc_many (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpc_many1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpc_maybe_lift (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpcf_ctor_str ; 
 int /*<<< orphan*/  mpcf_strfold ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static mpc_val_t *mpcf_re_repeat(int n, mpc_val_t **xs) {
  int num;
  (void) n;
  if (!xs[1]) { return xs[0]; }
  if (strcmp(xs[1], "*") == 0) { free(xs[1]); return mpc_many(mpcf_strfold, xs[0]); }
  if (strcmp(xs[1], "+") == 0) { free(xs[1]); return mpc_many1(mpcf_strfold, xs[0]); }
  if (strcmp(xs[1], "?") == 0) { free(xs[1]); return mpc_maybe_lift(xs[0], mpcf_ctor_str); }
  num = *(int*)xs[1];
  free(xs[1]);
  
  return mpc_count(num, mpcf_strfold, xs[0], free);
}