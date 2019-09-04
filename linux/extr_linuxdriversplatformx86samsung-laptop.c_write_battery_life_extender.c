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
struct samsung_laptop {TYPE_1__* config; } ;
struct sabi_data {int* data; } ;
struct sabi_commands {int /*<<< orphan*/  set_battery_life_extender; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_2__ {struct sabi_commands commands; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct sabi_data*,int /*<<< orphan*/ ,int) ; 
 int sabi_command (struct samsung_laptop*,int /*<<< orphan*/ ,struct sabi_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_battery_life_extender(struct samsung_laptop *samsung,
				       int enabled)
{
	const struct sabi_commands *commands = &samsung->config->commands;
	struct sabi_data data;

	memset(&data, 0, sizeof(data));
	data.data[0] = 0x80 | enabled;
	return sabi_command(samsung, commands->set_battery_life_extender,
			    &data, NULL);
}