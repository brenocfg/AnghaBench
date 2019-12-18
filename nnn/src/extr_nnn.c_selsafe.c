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
 scalar_t__ ENOENT ; 
 int FALSE ; 
 size_t NONE_SELECTED ; 
 int R_OK ; 
 int TRUE ; 
 int W_OK ; 
 int access (int /*<<< orphan*/ ,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  g_selpath ; 
 char** messages ; 
 int /*<<< orphan*/  printmsg (char*) ; 
 int /*<<< orphan*/  printwarn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool selsafe(void)
{
	/* Fail if selection file path not generated */
	if (!g_selpath) {
		printmsg("selection file not found");
		return FALSE;
	}

	/* Fail if selection file path isn't accessible */
	if (access(g_selpath, R_OK | W_OK) == -1) {
		errno == ENOENT ? printmsg(messages[NONE_SELECTED]) : printwarn(NULL);
		return FALSE;
	}

	return TRUE;
}