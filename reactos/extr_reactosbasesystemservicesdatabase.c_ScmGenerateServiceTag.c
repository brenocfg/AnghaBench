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
struct TYPE_4__ {int dwServiceType; } ;
struct TYPE_5__ {int dwTag; TYPE_1__ Status; } ;
typedef  TYPE_2__* PSERVICE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int SERVICE_WIN32 ; 
 int ServiceTag ; 

DWORD
ScmGenerateServiceTag(PSERVICE lpServiceRecord)
{
    /* Check for an overflow */
    if (ServiceTag == -1)
    {
        return ERROR_INVALID_DATA;
    }

    /* This is only valid for Win32 services */
    if (!(lpServiceRecord->Status.dwServiceType & SERVICE_WIN32))
    {
        return ERROR_INVALID_PARAMETER;
    }

    /* Increment the tag counter and set it */
    ServiceTag = ServiceTag % 0xFFFFFFFF + 1;
    lpServiceRecord->dwTag = ServiceTag;

    return ERROR_SUCCESS;
}