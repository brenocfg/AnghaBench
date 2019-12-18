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
struct obs_core_hotkeys {TYPE_1__* platform_context; } ;
struct TYPE_2__ {int /*<<< orphan*/ * base_keysyms; } ;

/* Variables and functions */
 size_t OBS_KEY_LAST_VALUE ; 
 int /*<<< orphan*/  get_keysym (size_t) ; 

__attribute__((used)) static inline void fill_base_keysyms(struct obs_core_hotkeys *hotkeys)
{
	for (size_t i = 0; i < OBS_KEY_LAST_VALUE; i++)
		hotkeys->platform_context->base_keysyms[i] = get_keysym(i);
}