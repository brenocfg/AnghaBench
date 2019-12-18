#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int dmSize; int dmDisplayFrequency; } ;
typedef  TYPE_1__ DEVMODEW ;

/* Variables and functions */
 int /*<<< orphan*/  ENUM_CURRENT_SETTINGS ; 
 int /*<<< orphan*/  EnumDisplaySettingsW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static double get_refresh_rate_from_gdi(const wchar_t *device)
{
    DEVMODEW dm = { .dmSize = sizeof dm };
    if (!EnumDisplaySettingsW(device, ENUM_CURRENT_SETTINGS, &dm))
        return 0.0;

    // May return 0 or 1 which "represent the display hardware's default refresh rate"
    // https://msdn.microsoft.com/en-us/library/windows/desktop/dd183565%28v=vs.85%29.aspx
    // mpv validates this value with a threshold of 1, so don't return exactly 1
    if (dm.dmDisplayFrequency == 1)
        return 0.0;

    // dm.dmDisplayFrequency is an integer which is rounded down, so it's
    // highly likely that 23 represents 24/1.001, 59 represents 60/1.001, etc.
    // A caller can always reproduce the original value by using floor.
    double rv = dm.dmDisplayFrequency;
    switch (dm.dmDisplayFrequency) {
        case  23:
        case  29:
        case  47:
        case  59:
        case  71:
        case  89:
        case  95:
        case 119:
        case 143:
            rv = (rv + 1) / 1.001;
    }

    return rv;
}