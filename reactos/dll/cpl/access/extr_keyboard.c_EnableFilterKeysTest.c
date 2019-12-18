#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {int /*<<< orphan*/  dwFlags; } ;
struct TYPE_4__ {TYPE_2__ filterKeys; } ;
typedef  TYPE_1__* PGLOBAL_DATA ;
typedef  int /*<<< orphan*/  FILTERKEYS ;

/* Variables and functions */
 int /*<<< orphan*/  FKF_FILTERKEYSON ; 
 int /*<<< orphan*/  FKF_INDICATOR ; 
 int /*<<< orphan*/  SPI_SETFILTERKEYS ; 
 int /*<<< orphan*/  SystemParametersInfo (int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
EnableFilterKeysTest(PGLOBAL_DATA pGlobalData)
{
    pGlobalData->filterKeys.dwFlags |= FKF_FILTERKEYSON;
    pGlobalData->filterKeys.dwFlags &= ~FKF_INDICATOR;

    SystemParametersInfo(SPI_SETFILTERKEYS,
                         sizeof(FILTERKEYS),
                         &pGlobalData->filterKeys,
                         0);
}