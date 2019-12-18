#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pos; } ;
struct TYPE_6__ {int backtrack; int marks_num; scalar_t__ type; TYPE_1__ state; int /*<<< orphan*/  file; int /*<<< orphan*/ * lasts; int /*<<< orphan*/  last; TYPE_1__* marks; } ;
typedef  TYPE_2__ mpc_input_t ;

/* Variables and functions */
 scalar_t__ MPC_INPUT_FILE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_input_unmark (TYPE_2__*) ; 

__attribute__((used)) static void mpc_input_rewind(mpc_input_t *i) {
  
  if (i->backtrack < 1) { return; }
  
  i->state = i->marks[i->marks_num-1];
  i->last  = i->lasts[i->marks_num-1];
  
  if (i->type == MPC_INPUT_FILE) {
    fseek(i->file, i->state.pos, SEEK_SET);
  }
  
  mpc_input_unmark(i);
}