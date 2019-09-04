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
struct TYPE_3__ {int thread_disable_press; } ;
struct TYPE_4__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock () ; 
 TYPE_2__* obs ; 
 int /*<<< orphan*/  unlock () ; 

void obs_hotkey_enable_background_press(bool enable)
{
	if (!lock())
		return;

	obs->hotkeys.thread_disable_press = !enable;
	unlock();
}