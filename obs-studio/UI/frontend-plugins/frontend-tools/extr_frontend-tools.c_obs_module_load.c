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

/* Variables and functions */
 int /*<<< orphan*/  InitCaptions () ; 
 int /*<<< orphan*/  InitOutputTimer () ; 
 int /*<<< orphan*/  InitSceneSwitcher () ; 
 int /*<<< orphan*/  InitScripts () ; 

bool obs_module_load(void)
{
#if defined(_WIN32) && BUILD_CAPTIONS
	InitCaptions();
#endif
	InitSceneSwitcher();
	InitOutputTimer();
#if ENABLE_SCRIPTING
	InitScripts();
#endif
	return true;
}