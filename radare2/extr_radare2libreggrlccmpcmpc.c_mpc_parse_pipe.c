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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  mpc_input_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpc_input_new_pipe (char const*,int /*<<< orphan*/ *) ; 
 int mpc_parse_input (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mpc_parse_pipe(const char *filename, FILE *pipe, mpc_parser_t *p, mpc_result_t *r) {
  int x;
  mpc_input_t *i = mpc_input_new_pipe(filename, pipe);
  x = mpc_parse_input(i, p, r);
  mpc_input_delete(i);
  return x;
}