#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {int /*<<< orphan*/  dwServiceType; } ;
struct TYPE_9__ {TYPE_1__ ServiceStatus; int /*<<< orphan*/ * lpServiceName; int /*<<< orphan*/  lpDisplayName; } ;
struct TYPE_8__ {int /*<<< orphan*/  hDependsTreeView2; } ;
typedef  TYPE_2__* PDEPENDDATA ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  TYPE_3__* LPENUM_SERVICE_STATUSW ;
typedef  int /*<<< orphan*/ * HTREEITEM ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AddItemToTreeView (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AllocAndLoadString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  IDS_NO_DEPENDS ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 TYPE_3__* TV2_GetDependants (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  TV2_HasDependantServices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hInstance ; 

VOID
TV2_AddDependantsToTree(PDEPENDDATA pDependData,
                        HTREEITEM hParent,
                        LPWSTR lpServiceName)
{

    LPENUM_SERVICE_STATUSW lpServiceStatus;
    LPWSTR lpNoDepends;
    DWORD count, i;
    BOOL bHasChildren;

    /* Get a list of service dependents */
    lpServiceStatus = TV2_GetDependants(lpServiceName, &count);
    if (lpServiceStatus)
    {
        for (i = 0; i < count; i++)
        {
            /* Does this item need a +/- box? */
            bHasChildren = TV2_HasDependantServices(lpServiceStatus[i].lpServiceName);

            /* Add it */
            AddItemToTreeView(pDependData->hDependsTreeView2,
                              hParent,
                              lpServiceStatus[i].lpDisplayName,
                              lpServiceStatus[i].lpServiceName,
                              lpServiceStatus[i].ServiceStatus.dwServiceType,
                              bHasChildren);
        }

        HeapFree(GetProcessHeap(),
                 0,
                 lpServiceStatus);
    }
    else
    {
        /* If there is no parent, set the tree to 'no dependencies' */
        if (!hParent)
        {
            /* Load the 'No dependencies' string */
            AllocAndLoadString(&lpNoDepends, hInstance, IDS_NO_DEPENDS);

            AddItemToTreeView(pDependData->hDependsTreeView2,
                              NULL,
                              lpNoDepends,
                              NULL,
                              0,
                              FALSE);

            LocalFree(lpNoDepends);

            /* Disable the window */
            EnableWindow(pDependData->hDependsTreeView2, FALSE);
        }
    }
}