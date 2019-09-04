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
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__* PWSTR ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UNICODE_NULL ; 
 int /*<<< orphan*/  wcstoul (scalar_t__*,scalar_t__**,int) ; 

__attribute__((used)) static
BOOL
ParseId(
    PWSTR pszId,
    PULONG pulId)
{
    PWSTR startPtr, endPtr;
    ULONG ulId = 0;
    BOOL bResult = FALSE;

    startPtr = pszId;
    endPtr = NULL;
    ulId = wcstoul(startPtr, &endPtr, 10);
    if (endPtr != NULL && *endPtr == UNICODE_NULL)
    {
        bResult = TRUE;

        if (pulId != NULL)
            *pulId = ulId;
    }

    return bResult;
}