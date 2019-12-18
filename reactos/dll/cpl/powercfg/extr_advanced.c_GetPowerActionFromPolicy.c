#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ Action; int Flags; scalar_t__ EventCode; } ;
struct TYPE_5__ {scalar_t__ SystemS3; scalar_t__ SystemS2; scalar_t__ SystemS1; scalar_t__ HiberFilePresent; scalar_t__ SystemS4; } ;
typedef  TYPE_1__* PSYSTEM_POWER_CAPABILITIES ;
typedef  TYPE_2__ POWER_ACTION_POLICY ;
typedef  scalar_t__ POWER_ACTION ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int POWER_ACTION_QUERY_ALLOWED ; 
 int POWER_ACTION_UI_ALLOWED ; 
 scalar_t__ POWER_FORCE_TRIGGER_RESET ; 
 scalar_t__ POWER_USER_NOTIFY_BUTTON ; 
 scalar_t__ POWER_USER_NOTIFY_SHUTDOWN ; 
 scalar_t__ PowerActionHibernate ; 
 scalar_t__ PowerActionNone ; 
 scalar_t__ PowerActionShutdown ; 
 scalar_t__ PowerActionSleep ; 
 scalar_t__ PowerActionWarmEject ; 

POWER_ACTION
GetPowerActionFromPolicy(
    POWER_ACTION_POLICY *Policy,
    PSYSTEM_POWER_CAPABILITIES spc,
    BOOL bIsLid)
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
        if ((poAction == PowerActionHibernate) && !(spc->SystemS4 && spc->HiberFilePresent))
            poAction = PowerActionSleep;
        if ((poAction == PowerActionSleep) && !(spc->SystemS1 || spc->SystemS2 || spc->SystemS3))
        {
            if (bIsLid)
                poAction = PowerActionNone;
            else
                poAction = PowerActionShutdown;
        }
    }

    return poAction;
}