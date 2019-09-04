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
struct TYPE_9__ {TYPE_2__* pDlgInfo; int /*<<< orphan*/  hDependsImageList; } ;
struct TYPE_8__ {TYPE_1__* pService; } ;
struct TYPE_7__ {int /*<<< orphan*/  lpServiceName; } ;
typedef  TYPE_3__* PDEPENDDATA ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDI_DRIVER ; 
 int /*<<< orphan*/  IDI_NODEPENDS ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 int /*<<< orphan*/  InitImageList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXSMICON ; 
 int /*<<< orphan*/  TV1_Initialize (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TV2_Initialize (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
InitDependPage(PDEPENDDATA pDependData)
{
    /* Initialize the image list */
    pDependData->hDependsImageList = InitImageList(IDI_NODEPENDS,
                                                   IDI_DRIVER,
                                                   GetSystemMetrics(SM_CXSMICON),
                                                   GetSystemMetrics(SM_CXSMICON),
                                                   IMAGE_ICON);

    /* Set the first tree view */
    TV1_Initialize(pDependData, pDependData->pDlgInfo->pService->lpServiceName);

    /* Set the second tree view */
    TV2_Initialize(pDependData, pDependData->pDlgInfo->pService->lpServiceName);
}