#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  signals; } ;
struct obs_output {TYPE_1__ context; int /*<<< orphan*/  reconnect_retry_cur_sec; } ;
struct calldata {int dummy; } ;
typedef  int /*<<< orphan*/  stack ;

/* Variables and functions */
 int /*<<< orphan*/  calldata_init_fixed (struct calldata*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  calldata_set_int (struct calldata*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calldata_set_ptr (struct calldata*,char*,struct obs_output*) ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char*,struct calldata*) ; 

__attribute__((used)) static inline void signal_reconnect(struct obs_output *output)
{
	struct calldata params;
	uint8_t stack[128];

	calldata_init_fixed(&params, stack, sizeof(stack));
	calldata_set_int(&params, "timeout_sec",
			 output->reconnect_retry_cur_sec);
	calldata_set_ptr(&params, "output", output);
	signal_handler_signal(output->context.signals, "reconnect", &params);
}