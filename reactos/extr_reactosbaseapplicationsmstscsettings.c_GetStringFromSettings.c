#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t NumSettings; TYPE_2__* pSettings; } ;
struct TYPE_5__ {int /*<<< orphan*/ * s; } ;
struct TYPE_6__ {int Type; TYPE_1__ Value; int /*<<< orphan*/  Key; } ;
typedef  TYPE_3__* PRDPSETTINGS ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  size_t INT ;

/* Variables and functions */
 scalar_t__ wcscmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

LPWSTR
GetStringFromSettings(PRDPSETTINGS pRdpSettings,
                      LPWSTR lpKey)
{
    LPWSTR lpValue = NULL;

    if (pRdpSettings)
    {
        INT i;

        for (i = 0; i < pRdpSettings->NumSettings; i++)
        {
            if (wcscmp(pRdpSettings->pSettings[i].Key, lpKey) == 0)
            {
                if (pRdpSettings->pSettings[i].Type == L's')
                {
                    lpValue = pRdpSettings->pSettings[i].Value.s;
                    break;
                }
            }
        }
    }

    return lpValue;
}