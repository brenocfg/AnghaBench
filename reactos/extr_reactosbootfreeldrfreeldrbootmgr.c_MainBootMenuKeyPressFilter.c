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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DoOptionsMenu () ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KEY_F8 ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN MainBootMenuKeyPressFilter(ULONG KeyPress)
{
    if (KeyPress == KEY_F8)
    {
        DoOptionsMenu();
        return TRUE;
    }

    /* We didn't handle the key */
    return FALSE;
}