#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct calldata {int dummy; } ;
typedef  int /*<<< orphan*/  stack ;
struct TYPE_6__ {int /*<<< orphan*/  signals; } ;
struct TYPE_7__ {int enabled; TYPE_1__ context; } ;
typedef  TYPE_2__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  calldata_init_fixed (struct calldata*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  calldata_set_bool (struct calldata*,char*,int) ; 
 int /*<<< orphan*/  calldata_set_ptr (struct calldata*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char*,struct calldata*) ; 

void obs_source_set_enabled(obs_source_t *source, bool enabled)
{
	struct calldata data;
	uint8_t stack[128];

	if (!obs_source_valid(source, "obs_source_set_enabled"))
		return;

	source->enabled = enabled;

	calldata_init_fixed(&data, stack, sizeof(stack));
	calldata_set_ptr(&data, "source", source);
	calldata_set_bool(&data, "enabled", enabled);

	signal_handler_signal(source->context.signals, "enable", &data);
}