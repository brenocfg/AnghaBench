#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * hDependsImageList; int /*<<< orphan*/  hDependsTreeView2; int /*<<< orphan*/  hDependsWnd; } ;
typedef  TYPE_1__* PDEPENDDATA ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_DEPEND_TREE2 ; 
 int /*<<< orphan*/  ImageList_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TV2_AddDependantsToTree (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVSIL_NORMAL ; 
 int /*<<< orphan*/  TreeView_SetImageList (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOL
TV2_Initialize(PDEPENDDATA pDependData,
               LPWSTR lpServiceName)
{
    BOOL bRet = FALSE;

    /* Associate the imagelist with TV2 */
    pDependData->hDependsTreeView2 = GetDlgItem(pDependData->hDependsWnd, IDC_DEPEND_TREE2);
    if (!pDependData->hDependsTreeView2)
    {
        ImageList_Destroy(pDependData->hDependsImageList);
        pDependData->hDependsImageList = NULL;
        return FALSE;
    }
    (void)TreeView_SetImageList(pDependData->hDependsTreeView2,
                                pDependData->hDependsImageList,
                                TVSIL_NORMAL);

    /* Set the first items in the control */
    TV2_AddDependantsToTree(pDependData, NULL, lpServiceName);

    return bRet;
}