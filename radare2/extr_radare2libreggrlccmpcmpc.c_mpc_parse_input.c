#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  error; int /*<<< orphan*/  output; } ;
typedef  TYPE_1__ mpc_result_t ;
typedef  int /*<<< orphan*/  mpc_parser_t ;
typedef  int /*<<< orphan*/  mpc_input_t ;
struct TYPE_10__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ mpc_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  mpc_err_delete_internal (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mpc_err_export (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* mpc_err_fail (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mpc_err_merge (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_export (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mpc_parse_run (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__**) ; 
 int /*<<< orphan*/  mpc_state_invalid () ; 

int mpc_parse_input(mpc_input_t *i, mpc_parser_t *p, mpc_result_t *r) {
  int x;
  mpc_err_t *e = mpc_err_fail(i, "Unknown Error");
  e->state = mpc_state_invalid();
  x = mpc_parse_run(i, p, r, &e);
  if (x) {
    mpc_err_delete_internal(i, e);
    r->output = mpc_export(i, r->output);
  } else {
    r->error = mpc_err_export(i, mpc_err_merge(i, e, r->error));
  }
  return x;
}