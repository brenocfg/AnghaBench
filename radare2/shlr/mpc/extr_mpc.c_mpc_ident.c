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

/* Variables and functions */
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  mpc_alpha () ; 
 int /*<<< orphan*/  mpc_alphanum () ; 
 int /*<<< orphan*/ * mpc_and (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mpc_many (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mpc_or (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_underscore () ; 
 int /*<<< orphan*/  mpcf_strfold ; 

mpc_parser_t *mpc_ident(void) {
  mpc_parser_t *p0, *p1; 
  p0 = mpc_or(2, mpc_alpha(), mpc_underscore());
  p1 = mpc_many(mpcf_strfold, mpc_alphanum()); 
  return mpc_and(2, mpcf_strfold, p0, p1, free);
}