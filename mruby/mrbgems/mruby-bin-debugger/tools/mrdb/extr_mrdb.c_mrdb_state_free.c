#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_3__ {struct TYPE_3__* command; } ;

/* Variables and functions */
 TYPE_1__* _mrdb_state ; 
 int /*<<< orphan*/  mrb_debug_context_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
mrdb_state_free(mrb_state *mrb)
{
  mrb_debug_context_free(mrb);
  if (_mrdb_state) {
    mrb_free(mrb, _mrdb_state->command);
    mrb_free(mrb, _mrdb_state);
    _mrdb_state = NULL;
  }
}