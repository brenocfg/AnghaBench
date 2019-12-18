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
 int /*<<< orphan*/  mpc_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mpc_expect (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mpc_octdigits () ; 
 int /*<<< orphan*/  mpcf_oct ; 

mpc_parser_t *mpc_oct(void) { return mpc_expect(mpc_apply(mpc_octdigits(), mpcf_oct), "octadecimal"); }