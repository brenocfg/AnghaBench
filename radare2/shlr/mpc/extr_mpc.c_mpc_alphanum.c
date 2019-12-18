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
 int /*<<< orphan*/  mpc_alpha () ; 
 int /*<<< orphan*/  mpc_digit () ; 
 int /*<<< orphan*/ * mpc_expect (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mpc_or (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_underscore () ; 

mpc_parser_t *mpc_alphanum(void) { return mpc_expect(mpc_or(3, mpc_alpha(), mpc_digit(), mpc_underscore()), "alphanumeric"); }