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
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/ * mpc_and (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mpc_lift (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpcf_ctor_str ; 
 int /*<<< orphan*/  mpcf_strfold ; 

__attribute__((used)) static mpc_val_t *mpcf_re_and(int n, mpc_val_t **xs) {
  int i;
  mpc_parser_t *p = mpc_lift(mpcf_ctor_str);
  for (i = 0; i < n; i++) {
    p = mpc_and(2, mpcf_strfold, p, xs[i], free);
  }
  return p;
}