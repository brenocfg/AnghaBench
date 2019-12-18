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
struct obs_output {TYPE_1__ context; } ;
struct calldata {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  calldata_free (struct calldata*) ; 
 int /*<<< orphan*/  calldata_set_ptr (struct calldata*,char*,struct obs_output*) ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char const*,struct calldata*) ; 

__attribute__((used)) static inline void do_output_signal(struct obs_output *output,
				    const char *signal)
{
	struct calldata params = {0};
	calldata_set_ptr(&params, "output", output);
	signal_handler_signal(output->context.signals, signal, &params);
	calldata_free(&params);
}