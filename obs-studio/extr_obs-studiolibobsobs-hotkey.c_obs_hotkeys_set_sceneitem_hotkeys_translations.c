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
struct TYPE_3__ {void* sceneitem_hide; void* sceneitem_show; } ;
struct TYPE_4__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (void*) ; 
 void* bstrdup (char const*) ; 
 TYPE_2__* obs ; 

void obs_hotkeys_set_sceneitem_hotkeys_translations(
		const char *show, const char *hide)
{
#define SET_T(n) bfree(obs->hotkeys.sceneitem_##n); \
	obs->hotkeys.sceneitem_##n = bstrdup(n)
	SET_T(show);
	SET_T(hide);
#undef SET_T
}