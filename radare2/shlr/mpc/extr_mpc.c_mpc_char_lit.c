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
 int /*<<< orphan*/  mpc_any () ; 
 int /*<<< orphan*/  mpc_between (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mpc_escape () ; 
 int /*<<< orphan*/ * mpc_expect (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mpc_or (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

mpc_parser_t *mpc_char_lit(void) {
  return mpc_expect(mpc_between(mpc_or(2, mpc_escape(), mpc_any()), free, "'", "'"), "char");
}