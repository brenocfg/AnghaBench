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
struct TYPE_4__ {int /*<<< orphan*/  Tag; } ;
struct TYPE_5__ {int /*<<< orphan*/  ServiceEntry; TYPE_1__ Handle; } ;
typedef  int /*<<< orphan*/  SERVICE_HANDLE ;
typedef  scalar_t__ SC_HANDLE ;
typedef  TYPE_2__* PSERVICE_HANDLE ;
typedef  int /*<<< orphan*/  PSERVICE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SERVICE_TAG ; 

__attribute__((used)) static DWORD
ScmCreateServiceHandle(PSERVICE lpServiceEntry,
                       SC_HANDLE *Handle)
{
    PSERVICE_HANDLE Ptr;

    Ptr = HeapAlloc(GetProcessHeap(),
                    HEAP_ZERO_MEMORY,
                    sizeof(SERVICE_HANDLE));
    if (Ptr == NULL)
        return ERROR_NOT_ENOUGH_MEMORY;

    Ptr->Handle.Tag = SERVICE_TAG;

    Ptr->ServiceEntry = lpServiceEntry;

    *Handle = (SC_HANDLE)Ptr;

    return ERROR_SUCCESS;
}