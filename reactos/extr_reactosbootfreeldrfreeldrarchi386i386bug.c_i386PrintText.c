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
 int /*<<< orphan*/  MachVideoPutChar (char,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCREEN_ATTR ; 
 scalar_t__ i386_ScreenPosX ; 
 int /*<<< orphan*/  i386_ScreenPosY ; 

__attribute__((used)) static void
i386PrintText(char *pszText)
{
    char chr;
    while (1)
    {
        chr = *pszText++;

        if (chr == 0) break;
        if (chr == '\n')
        {
            i386_ScreenPosY++;
            i386_ScreenPosX = 0;
            continue;
        }

        MachVideoPutChar(chr, SCREEN_ATTR, i386_ScreenPosX, i386_ScreenPosY);
        i386_ScreenPosX++;
    }
}