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
struct TYPE_2__ {int /*<<< orphan*/  signals; } ;
struct obs_output {TYPE_1__ context; int /*<<< orphan*/  stop_code; int /*<<< orphan*/  last_error_message; } ;
struct calldata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  calldata_free (struct calldata*) ; 
 int /*<<< orphan*/  calldata_init (struct calldata*) ; 
 int /*<<< orphan*/  calldata_set_int (struct calldata*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calldata_set_ptr (struct calldata*,char*,struct obs_output*) ; 
 int /*<<< orphan*/  calldata_set_string (struct calldata*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char*,struct calldata*) ; 

__attribute__((used)) static inline void signal_stop(struct obs_output *output)
{
	struct calldata params;

	calldata_init(&params);
	calldata_set_string(&params, "last_error", output->last_error_message);
	calldata_set_int(&params, "code", output->stop_code);
	calldata_set_ptr(&params, "output", output);

	signal_handler_signal(output->context.signals, "stop", &params);

	calldata_free(&params);
}