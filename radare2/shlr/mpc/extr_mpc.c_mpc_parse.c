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
typedef  int /*<<< orphan*/  mpc_result_t ;
typedef  int /*<<< orphan*/  mpc_parser_t ;
typedef  int /*<<< orphan*/  mpc_input_t ;

/* Variables and functions */
 int /*<<< orphan*/  mpc_input_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpc_input_new_string (char const*,char const*) ; 
 int mpc_parse_input (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mpc_parse(const char *filename, const char *string, mpc_parser_t *p, mpc_result_t *r) {
  int x;
  mpc_input_t *i = mpc_input_new_string(filename, string);
  x = mpc_parse_input(i, p, r);
  mpc_input_delete(i);
  return x;
}