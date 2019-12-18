#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct handle_table {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  destructor; scalar_t__ refcount; int /*<<< orphan*/  dwType; } ;
typedef  TYPE_1__ OBJECTHDR ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  DESTRUCTOR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  alloc_handle (struct handle_table*,TYPE_1__*,int /*<<< orphan*/ *) ; 

HCRYPTKEY new_object(struct handle_table *lpTable, size_t cbSize, DWORD dwType, DESTRUCTOR destructor,
                        OBJECTHDR **ppObject)
{
    OBJECTHDR *pObject;
    HCRYPTKEY hObject;

    if (ppObject)
        *ppObject = NULL;

    pObject = HeapAlloc(GetProcessHeap(), 0, cbSize);
    if (!pObject)
        return (HCRYPTKEY)INVALID_HANDLE_VALUE;

    pObject->dwType = dwType;
    pObject->refcount = 0;
    pObject->destructor = destructor;

    if (!alloc_handle(lpTable, pObject, &hObject))
        HeapFree(GetProcessHeap(), 0, pObject);
    else
        if (ppObject)
            *ppObject = pObject;

    return hObject;
}