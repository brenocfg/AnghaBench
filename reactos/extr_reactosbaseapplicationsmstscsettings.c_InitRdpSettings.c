#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WCHAR ;
struct TYPE_5__ {scalar_t__ i; } ;
struct TYPE_7__ {TYPE_1__ Value; scalar_t__ Type; int /*<<< orphan*/  Key; } ;
struct TYPE_6__ {int NumSettings; TYPE_4__* pSettings; } ;
typedef  int /*<<< orphan*/  SETTINGS ;
typedef  TYPE_2__* PRDPSETTINGS ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int NUM_SETTINGS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * lpSettings ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL
InitRdpSettings(PRDPSETTINGS pRdpSettings)
{
    BOOL bRet = FALSE;

    pRdpSettings->pSettings = HeapAlloc(GetProcessHeap(),
                                        0,
                                        sizeof(SETTINGS) * NUM_SETTINGS);
    if (pRdpSettings->pSettings)
    {
        INT i;

        for (i = 0; i < NUM_SETTINGS; i++)
        {
            wcscpy(pRdpSettings->pSettings[i].Key, lpSettings[i]);
            pRdpSettings->pSettings[i].Type = (WCHAR)0;
            pRdpSettings->pSettings[i].Value.i = 0;
        }

        pRdpSettings->NumSettings = NUM_SETTINGS;

        bRet = TRUE;
    }

    return bRet;
}