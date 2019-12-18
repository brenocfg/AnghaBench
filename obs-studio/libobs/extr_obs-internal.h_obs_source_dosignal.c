#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  signals; int /*<<< orphan*/  private; } ;
struct obs_source {TYPE_1__ context; } ;
struct calldata {int dummy; } ;
typedef  int /*<<< orphan*/  stack ;
struct TYPE_4__ {int /*<<< orphan*/  signals; } ;

/* Variables and functions */
 int /*<<< orphan*/  calldata_init_fixed (struct calldata*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  calldata_set_ptr (struct calldata*,char*,struct obs_source*) ; 
 TYPE_2__* obs ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char const*,struct calldata*) ; 

__attribute__((used)) static inline void obs_source_dosignal(struct obs_source *source,
				       const char *signal_obs,
				       const char *signal_source)
{
	struct calldata data;
	uint8_t stack[128];

	calldata_init_fixed(&data, stack, sizeof(stack));
	calldata_set_ptr(&data, "source", source);
	if (signal_obs && !source->context.private)
		signal_handler_signal(obs->signals, signal_obs, &data);
	if (signal_source)
		signal_handler_signal(source->context.signals, signal_source,
				      &data);
}