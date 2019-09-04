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
 int /*<<< orphan*/ * mpc_between (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 

mpc_parser_t *mpc_braces(mpc_parser_t *a, mpc_dtor_t ad)   { return mpc_between(a, ad, "<", ">"); }