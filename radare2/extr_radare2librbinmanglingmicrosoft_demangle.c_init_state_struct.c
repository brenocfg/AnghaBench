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
struct TYPE_3__ {char* buff_for_parsing; int /*<<< orphan*/  err; scalar_t__ amount_of_read_chars; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ SStateInfo ;

/* Variables and functions */
 int /*<<< orphan*/  eTCStateMachineErrOK ; 
 int /*<<< orphan*/  eTCStateStart ; 

__attribute__((used)) static void init_state_struct(SStateInfo *state, char *buff_for_parsing) {
	state->state = eTCStateStart;
	state->buff_for_parsing = buff_for_parsing;
	state->amount_of_read_chars = 0;
	state->err = eTCStateMachineErrOK;
}