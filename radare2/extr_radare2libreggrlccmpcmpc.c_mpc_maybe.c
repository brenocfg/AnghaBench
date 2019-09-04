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
 int /*<<< orphan*/ * mpc_maybe_lift (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpcf_ctor_null ; 

mpc_parser_t *mpc_maybe(mpc_parser_t *a) {
  return mpc_maybe_lift(a, mpcf_ctor_null);
}