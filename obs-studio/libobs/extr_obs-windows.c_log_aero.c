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
typedef  int /*<<< orphan*/  (* dwm_is_composition_enabled_t ) (int*) ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ ) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LoadLibraryW (char*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int win_ver ; 

__attribute__((used)) static void log_aero(void)
{
	dwm_is_composition_enabled_t composition_enabled = NULL;

	const char *aeroMessage =
		win_ver >= 0x602
			? " (Aero is always on for windows 8 and above)"
			: "";

	HMODULE dwm = LoadLibraryW(L"dwmapi");
	BOOL bComposition = true;

	if (!dwm) {
		return;
	}

	composition_enabled = (dwm_is_composition_enabled_t)GetProcAddress(
		dwm, "DwmIsCompositionEnabled");
	if (!composition_enabled) {
		FreeLibrary(dwm);
		return;
	}

	composition_enabled(&bComposition);
	blog(LOG_INFO, "Aero is %s%s", bComposition ? "Enabled" : "Disabled",
	     aeroMessage);
}