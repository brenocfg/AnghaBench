#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct obs_hotkey_internal_enum_forward {void* member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_hotkey_enum_func ;

/* Variables and functions */
 int /*<<< orphan*/  enum_hotkey ; 
 int /*<<< orphan*/  enum_hotkeys (int /*<<< orphan*/ ,struct obs_hotkey_internal_enum_forward*) ; 
 int /*<<< orphan*/  lock () ; 
 int /*<<< orphan*/  unlock () ; 

void obs_enum_hotkeys(obs_hotkey_enum_func func, void *data)
{
	struct obs_hotkey_internal_enum_forward forwarder = {func, data};
	if (!lock())
		return;

	enum_hotkeys(enum_hotkey, &forwarder);
	unlock();
}