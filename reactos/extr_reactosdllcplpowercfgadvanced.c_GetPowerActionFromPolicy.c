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
struct TYPE_3__ {scalar_t__ Action; int Flags; scalar_t__ EventCode; } ;
typedef  TYPE_1__ POWER_ACTION_POLICY ;
typedef  scalar_t__ POWER_ACTION ;

/* Variables and functions */
 int POWER_ACTION_QUERY_ALLOWED ; 
 int POWER_ACTION_UI_ALLOWED ; 
 scalar_t__ POWER_FORCE_TRIGGER_RESET ; 
 scalar_t__ POWER_USER_NOTIFY_BUTTON ; 
 scalar_t__ POWER_USER_NOTIFY_SHUTDOWN ; 
 scalar_t__ PowerActionNone ; 
 scalar_t__ PowerActionShutdown ; 
 scalar_t__ PowerActionWarmEject ; 

POWER_ACTION
GetPowerActionFromPolicy(POWER_ACTION_POLICY *Policy)
{
    POWER_ACTION poAction = PowerActionNone;
    /*

    TCHAR szBuffer[MAX_PATH];

    // Note: Windows XP SP2+ does not return the PowerAction code
    // for PowerActionWarmEject + PowerActionShutdown but sets it
    // to PowerActionNone and sets the Flags & EventCode


     _stprintf(szBuffer, L"Action: %x EventCode %x Flags %x",Policy->Action, Policy->EventCode, Policy->Flags);
     MessageBoxW(NULL, szBuffer, NULL, MB_OK);

    */

    if (Policy->Action == PowerActionNone)
    {
        if (Policy->Flags == (POWER_ACTION_UI_ALLOWED | POWER_ACTION_QUERY_ALLOWED))
        {
            if (Policy->EventCode  == POWER_FORCE_TRIGGER_RESET)
            {
                poAction = PowerActionNone;
            }
            else if (Policy->EventCode  == POWER_USER_NOTIFY_BUTTON)
            {
                poAction = PowerActionWarmEject;
            }
            else if (Policy->EventCode == POWER_USER_NOTIFY_SHUTDOWN)
            {
                poAction = PowerActionShutdown;
            }
        }
    }
    else
    {
        poAction = Policy->Action;
    }

    return poAction;
}