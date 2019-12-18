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
struct handle_table {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  OBJECTHDR ;
typedef  scalar_t__ HCRYPTKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,struct handle_table*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  alloc_handle (struct handle_table*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  lookup_handle (struct handle_table*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

BOOL copy_handle(struct handle_table *lpTable, HCRYPTKEY handle, DWORD dwType, HCRYPTKEY *copy)
{
    OBJECTHDR *pObject;
    BOOL ret;

    TRACE("(lpTable=%p, handle=%ld, copy=%p)\n", lpTable, handle, copy);

    EnterCriticalSection(&lpTable->mutex);
    if (!lookup_handle(lpTable, handle, dwType, &pObject)) 
    {
        *copy = (HCRYPTKEY)INVALID_HANDLE_VALUE;
        LeaveCriticalSection(&lpTable->mutex);
        return FALSE;
    }

    ret = alloc_handle(lpTable, pObject, copy);
    LeaveCriticalSection(&lpTable->mutex);
    return ret;
}