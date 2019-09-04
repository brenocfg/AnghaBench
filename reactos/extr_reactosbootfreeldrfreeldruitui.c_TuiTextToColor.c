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
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  PCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_BLACK ; 
 int /*<<< orphan*/  COLOR_BLUE ; 
 int /*<<< orphan*/  COLOR_BROWN ; 
 int /*<<< orphan*/  COLOR_CYAN ; 
 int /*<<< orphan*/  COLOR_DARKGRAY ; 
 int /*<<< orphan*/  COLOR_GRAY ; 
 int /*<<< orphan*/  COLOR_GREEN ; 
 int /*<<< orphan*/  COLOR_LIGHTBLUE ; 
 int /*<<< orphan*/  COLOR_LIGHTCYAN ; 
 int /*<<< orphan*/  COLOR_LIGHTGREEN ; 
 int /*<<< orphan*/  COLOR_LIGHTMAGENTA ; 
 int /*<<< orphan*/  COLOR_LIGHTRED ; 
 int /*<<< orphan*/  COLOR_MAGENTA ; 
 int /*<<< orphan*/  COLOR_RED ; 
 int /*<<< orphan*/  COLOR_WHITE ; 
 int /*<<< orphan*/  COLOR_YELLOW ; 
 scalar_t__ _stricmp (int /*<<< orphan*/ ,char*) ; 

UCHAR TuiTextToColor(PCSTR ColorText)
{
    if (_stricmp(ColorText, "Black") == 0)
        return COLOR_BLACK;
    else if (_stricmp(ColorText, "Blue") == 0)
        return COLOR_BLUE;
    else if (_stricmp(ColorText, "Green") == 0)
        return COLOR_GREEN;
    else if (_stricmp(ColorText, "Cyan") == 0)
        return COLOR_CYAN;
    else if (_stricmp(ColorText, "Red") == 0)
        return COLOR_RED;
    else if (_stricmp(ColorText, "Magenta") == 0)
        return COLOR_MAGENTA;
    else if (_stricmp(ColorText, "Brown") == 0)
        return COLOR_BROWN;
    else if (_stricmp(ColorText, "Gray") == 0)
        return COLOR_GRAY;
    else if (_stricmp(ColorText, "DarkGray") == 0)
        return COLOR_DARKGRAY;
    else if (_stricmp(ColorText, "LightBlue") == 0)
        return COLOR_LIGHTBLUE;
    else if (_stricmp(ColorText, "LightGreen") == 0)
        return COLOR_LIGHTGREEN;
    else if (_stricmp(ColorText, "LightCyan") == 0)
        return COLOR_LIGHTCYAN;
    else if (_stricmp(ColorText, "LightRed") == 0)
        return COLOR_LIGHTRED;
    else if (_stricmp(ColorText, "LightMagenta") == 0)
        return COLOR_LIGHTMAGENTA;
    else if (_stricmp(ColorText, "Yellow") == 0)
        return COLOR_YELLOW;
    else if (_stricmp(ColorText, "White") == 0)
        return COLOR_WHITE;

    return COLOR_BLACK;
}