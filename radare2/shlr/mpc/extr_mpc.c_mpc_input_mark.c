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
typedef  int /*<<< orphan*/  mpc_state_t ;
struct TYPE_3__ {int backtrack; int marks_num; int marks_slots; scalar_t__ type; int /*<<< orphan*/  buffer; int /*<<< orphan*/  last; int /*<<< orphan*/ * lasts; int /*<<< orphan*/  state; int /*<<< orphan*/ * marks; } ;
typedef  TYPE_1__ mpc_input_t ;

/* Variables and functions */
 scalar_t__ MPC_INPUT_PIPE ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 void* realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mpc_input_mark(mpc_input_t *i) {
  
  if (i->backtrack < 1) { return; }
  
  i->marks_num++;
  
  if (i->marks_num > i->marks_slots) {
    i->marks_slots = i->marks_num + i->marks_num / 2;
    i->marks = realloc(i->marks, sizeof(mpc_state_t) * i->marks_slots);
    i->lasts = realloc(i->lasts, sizeof(char) * i->marks_slots);
  }

  i->marks[i->marks_num-1] = i->state;
  i->lasts[i->marks_num-1] = i->last;
  
  if (i->type == MPC_INPUT_PIPE && i->marks_num == 1) {
    i->buffer = calloc(1, 1);
  }
  
}