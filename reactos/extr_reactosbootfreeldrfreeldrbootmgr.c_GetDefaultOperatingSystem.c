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
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  size_t ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  SystemPartition; } ;
typedef  int /*<<< orphan*/ * PCSTR ;
typedef  TYPE_1__ OperatingSystemItem ;
typedef  int /*<<< orphan*/  DefaultOSText ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/ * CmdLineGetDefaultOS () ; 
 int /*<<< orphan*/  IniOpenSection (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ IniReadSettingByName (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ _stricmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ULONG GetDefaultOperatingSystem(OperatingSystemItem* OperatingSystemList, ULONG OperatingSystemCount)
{
    CHAR      DefaultOSText[80];
    PCSTR     DefaultOSName;
    ULONG_PTR SectionId;
    ULONG     DefaultOS = 0;
    ULONG     Idx;

    if (!IniOpenSection("FreeLoader", &SectionId))
        return 0;

    DefaultOSName = CmdLineGetDefaultOS();
    if (DefaultOSName == NULL)
    {
        if (IniReadSettingByName(SectionId, "DefaultOS", DefaultOSText, sizeof(DefaultOSText)))
        {
            DefaultOSName = DefaultOSText;
        }
    }

    if (DefaultOSName != NULL)
    {
        for (Idx = 0; Idx < OperatingSystemCount; Idx++)
        {
            if (_stricmp(DefaultOSName, OperatingSystemList[Idx].SystemPartition) == 0)
            {
                DefaultOS = Idx;
                break;
            }
        }
    }

    return DefaultOS;
}