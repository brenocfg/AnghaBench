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
 int /*<<< orphan*/  DARK_FILL ; 
 int /*<<< orphan*/  LIGHT_FILL ; 
 int /*<<< orphan*/  MEDIUM_FILL ; 
 scalar_t__ _stricmp (int /*<<< orphan*/ ,char*) ; 

UCHAR TuiTextToFillStyle(PCSTR FillStyleText)
{
    if (_stricmp(FillStyleText, "Light") == 0)
    {
        return LIGHT_FILL;
    }
    else if (_stricmp(FillStyleText, "Medium") == 0)
    {
        return MEDIUM_FILL;
    }
    else if (_stricmp(FillStyleText, "Dark") == 0)
    {
        return DARK_FILL;
    }

    return LIGHT_FILL;
}