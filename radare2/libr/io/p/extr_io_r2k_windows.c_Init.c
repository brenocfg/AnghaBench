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
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ InitDriver () ; 
 scalar_t__ InstallService (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveService (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartStopService (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 scalar_t__ strlen (char const*) ; 

int Init (const char * driverPath) {
	BOOL ret = FALSE;
	if (InitDriver () == FALSE) {
		if (strlen (driverPath)) {
			StartStopService (TEXT ("r2k"),TRUE);
			RemoveService (TEXT ("r2k"));
			eprintf ("Installing driver: %s\n", driverPath);
			if (InstallService (driverPath, TEXT ("r2k"), TEXT ("r2k"))) {
				StartStopService (TEXT ("r2k"),FALSE);
				ret = InitDriver ();
			}
		} else {
			eprintf ("Error initalizating driver, try r2k://pathtodriver\nEx: radare2.exe r2k://c:\\r2k.sys");
		}
	} else {
		eprintf ("Driver present [OK]\n");
		ret = TRUE;
	}
	return ret;
}