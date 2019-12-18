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
typedef  int /*<<< orphan*/  mpc_dtor_t ;

/* Variables and functions */
 int /*<<< orphan*/ * mpc_not_lift (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpcf_ctor_null ; 

mpc_parser_t *mpc_not(mpc_parser_t *a, mpc_dtor_t da) {
  return mpc_not_lift(a, da, mpcf_ctor_null);
}