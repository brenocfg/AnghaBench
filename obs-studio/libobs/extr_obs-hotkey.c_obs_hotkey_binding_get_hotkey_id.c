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
typedef  int /*<<< orphan*/  obs_hotkey_id ;
struct TYPE_3__ {int /*<<< orphan*/  hotkey_id; } ;
typedef  TYPE_1__ obs_hotkey_binding_t ;

/* Variables and functions */

obs_hotkey_id obs_hotkey_binding_get_hotkey_id(obs_hotkey_binding_t *binding)
{
	return binding->hotkey_id;
}