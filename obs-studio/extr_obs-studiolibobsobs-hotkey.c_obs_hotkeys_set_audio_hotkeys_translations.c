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
struct TYPE_3__ {void* push_to_talk; void* push_to_mute; void* unmute; void* mute; } ;
struct TYPE_4__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (void*) ; 
 void* bstrdup (char const*) ; 
 TYPE_2__* obs ; 

void obs_hotkeys_set_audio_hotkeys_translations(
		const char *mute, const char *unmute,
		const char *push_to_mute, const char *push_to_talk)
{
#define SET_T(n) bfree(obs->hotkeys.n); obs->hotkeys.n = bstrdup(n)
	SET_T(mute);
	SET_T(unmute);
	SET_T(push_to_mute);
	SET_T(push_to_talk);
#undef SET_T
}