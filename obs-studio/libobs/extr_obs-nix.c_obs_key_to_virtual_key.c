#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ obs_key_t ;
struct TYPE_5__ {TYPE_1__* platform_context; } ;
struct TYPE_6__ {TYPE_2__ hotkeys; } ;
struct TYPE_4__ {scalar_t__* base_keysyms; } ;

/* Variables and functions */
 scalar_t__ OBS_KEY_META ; 
 int XK_Super_L ; 
 TYPE_3__* obs ; 

int obs_key_to_virtual_key(obs_key_t key)
{
	if (key == OBS_KEY_META)
		return XK_Super_L;

	return (int)obs->hotkeys.platform_context->base_keysyms[(int)key];
}