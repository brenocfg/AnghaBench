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
struct TYPE_3__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ obs_output_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  enum_context_hotkeys (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enum_load_bindings ; 
 int /*<<< orphan*/  lock () ; 
 int /*<<< orphan*/  unlock () ; 

void obs_hotkeys_load_output(obs_output_t *output, obs_data_t *hotkeys)
{
	if (!output || !hotkeys)
		return;
	if (!lock())
		return;

	enum_context_hotkeys(&output->context, enum_load_bindings, hotkeys);
	unlock();
}