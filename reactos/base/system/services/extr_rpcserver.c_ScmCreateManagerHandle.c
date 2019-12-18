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
struct TYPE_5__ {int /*<<< orphan*/  DatabaseName; TYPE_1__ Handle; } ;
typedef  scalar_t__ SC_HANDLE ;
typedef  TYPE_2__* PMANAGER_HANDLE ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DatabaseName ; 
 int /*<<< orphan*/  ERROR_DATABASE_DOES_NOT_EXIST ; 
 int /*<<< orphan*/  ERROR_INVALID_NAME ; 
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MANAGER_HANDLE ; 
 int /*<<< orphan*/  MANAGER_TAG ; 
 int /*<<< orphan*/ * SERVICES_ACTIVE_DATABASEW ; 
 int /*<<< orphan*/ * SERVICES_FAILED_DATABASEW ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD
ScmCreateManagerHandle(LPWSTR lpDatabaseName,
                       SC_HANDLE *Handle)
{
    PMANAGER_HANDLE Ptr;

    if (lpDatabaseName == NULL)
        lpDatabaseName = SERVICES_ACTIVE_DATABASEW;

    if (_wcsicmp(lpDatabaseName, SERVICES_FAILED_DATABASEW) == 0)
    {
        DPRINT("Database %S, does not exist\n", lpDatabaseName);
        return ERROR_DATABASE_DOES_NOT_EXIST;
    }
    else if (_wcsicmp(lpDatabaseName, SERVICES_ACTIVE_DATABASEW) != 0)
    {
        DPRINT("Invalid Database name %S.\n", lpDatabaseName);
        return ERROR_INVALID_NAME;
    }

    Ptr = HeapAlloc(GetProcessHeap(),
                    HEAP_ZERO_MEMORY,
                    FIELD_OFFSET(MANAGER_HANDLE, DatabaseName[wcslen(lpDatabaseName) + 1]));
    if (Ptr == NULL)
        return ERROR_NOT_ENOUGH_MEMORY;

    Ptr->Handle.Tag = MANAGER_TAG;

    wcscpy(Ptr->DatabaseName, lpDatabaseName);

    *Handle = (SC_HANDLE)Ptr;

    return ERROR_SUCCESS;
}