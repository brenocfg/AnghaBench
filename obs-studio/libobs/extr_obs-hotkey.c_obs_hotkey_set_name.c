#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ obs_hotkey_t ;
typedef  int /*<<< orphan*/  obs_hotkey_id ;
struct TYPE_5__ {TYPE_3__* array; } ;
struct TYPE_6__ {TYPE_1__ hotkeys; } ;
struct TYPE_8__ {TYPE_2__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstrdup (char const*) ; 
 int /*<<< orphan*/  find_id (int /*<<< orphan*/ ,size_t*) ; 
 TYPE_4__* obs ; 

void obs_hotkey_set_name(obs_hotkey_id id, const char *name)
{
	size_t idx;

	if (!find_id(id, &idx))
		return;

	obs_hotkey_t *hotkey = &obs->hotkeys.hotkeys.array[idx];
	bfree(hotkey->name);
	hotkey->name = bstrdup(name);
}