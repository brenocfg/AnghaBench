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
 int /*<<< orphan*/  EnableMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDM_CLOSE_FILE ; 
 int /*<<< orphan*/  IDM_DEVPROPS ; 
 int /*<<< orphan*/  IDM_SWITCHVIEW ; 
 int MF_BYCOMMAND ; 
 int MF_GRAYED ; 
 int /*<<< orphan*/  hMainMenu ; 

void DisableMenuItems(void)
{
    EnableMenuItem(hMainMenu, IDM_CLOSE_FILE, MF_BYCOMMAND | MF_GRAYED);
    EnableMenuItem(hMainMenu, IDM_DEVPROPS, MF_BYCOMMAND | MF_GRAYED);
    EnableMenuItem(hMainMenu, IDM_SWITCHVIEW, MF_BYCOMMAND | MF_GRAYED);
}