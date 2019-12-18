#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct handle_table {unsigned int iEntries; int /*<<< orphan*/  mutex; TYPE_2__* paEntries; } ;
struct TYPE_4__ {TYPE_1__* pObject; } ;
struct TYPE_3__ {scalar_t__ dwType; } ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 unsigned int HANDLE2INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,struct handle_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL is_valid_handle(struct handle_table *lpTable, HCRYPTKEY handle, DWORD dwType)
{
    unsigned int index = HANDLE2INDEX(handle);
    BOOL ret = FALSE;

    TRACE("(lpTable=%p, handle=%ld)\n", lpTable, handle);
    
    EnterCriticalSection(&lpTable->mutex);
        
    /* We don't use zero handle values */
    if (!handle) goto exit;
 
    /* Check for index out of table bounds */    
    if (index >= lpTable->iEntries) goto exit;
    
    /* Check if this handle is currently allocated */
    if (!lpTable->paEntries[index].pObject) goto exit;
    
    /* Check if this handle references an object of the correct type. */
    if (lpTable->paEntries[index].pObject->dwType != dwType) goto exit;

    ret = TRUE;
exit:
    LeaveCriticalSection(&lpTable->mutex);
    return ret;
}