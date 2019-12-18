#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {long pos; } ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  file; int /*<<< orphan*/  string; TYPE_1__ state; } ;
typedef  TYPE_2__ mpc_input_t ;

/* Variables and functions */
 scalar_t__ MPC_INPUT_FILE ; 
 scalar_t__ MPC_INPUT_PIPE ; 
 scalar_t__ MPC_INPUT_STRING ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpc_input_terminated(mpc_input_t *i) {
  if (i->type == MPC_INPUT_STRING && i->state.pos == (long)strlen(i->string)) { return 1; }
  if (i->type == MPC_INPUT_FILE && feof(i->file)) { return 1; }
  if (i->type == MPC_INPUT_PIPE && feof(i->file)) { return 1; }
  return 0;
}