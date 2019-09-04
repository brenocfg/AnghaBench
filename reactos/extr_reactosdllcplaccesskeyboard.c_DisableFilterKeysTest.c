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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {int dwFlags; } ;
struct TYPE_5__ {int dwFlags; } ;
struct TYPE_6__ {TYPE_3__ filterKeys; TYPE_1__ oldFilterKeys; } ;
typedef  TYPE_2__* PGLOBAL_DATA ;
typedef  int /*<<< orphan*/  FILTERKEYS ;

/* Variables and functions */
 int FKF_FILTERKEYSON ; 
 int FKF_INDICATOR ; 
 int /*<<< orphan*/  SPI_SETFILTERKEYS ; 
 int /*<<< orphan*/  SystemParametersInfo (int /*<<< orphan*/ ,int,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
DisableFilterKeysTest(PGLOBAL_DATA pGlobalData)
{
    if (pGlobalData->oldFilterKeys.dwFlags & FKF_FILTERKEYSON)
    {
        pGlobalData->filterKeys.dwFlags |= FKF_FILTERKEYSON;
    }
    else
    {
        pGlobalData->filterKeys.dwFlags &= ~FKF_FILTERKEYSON;
    }

    if (pGlobalData->oldFilterKeys.dwFlags & FKF_INDICATOR)
    {
        pGlobalData->filterKeys.dwFlags |= FKF_INDICATOR;
    }
    else
    {
        pGlobalData->filterKeys.dwFlags &= ~FKF_INDICATOR;
    }

    SystemParametersInfo(SPI_SETFILTERKEYS,
                         sizeof(FILTERKEYS),
                         &pGlobalData->filterKeys,
                         0);
}