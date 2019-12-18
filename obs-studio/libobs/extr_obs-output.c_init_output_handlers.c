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
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_OBJ_TYPE_OUTPUT ; 
 int /*<<< orphan*/  obs_context_data_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  output_signals ; 
 int /*<<< orphan*/  signal_handler_add_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool init_output_handlers(struct obs_output *output, const char *name,
				 obs_data_t *settings, obs_data_t *hotkey_data)
{
	if (!obs_context_data_init(&output->context, OBS_OBJ_TYPE_OUTPUT,
				   settings, name, hotkey_data, false))
		return false;

	signal_handler_add_array(output->context.signals, output_signals);
	return true;
}