#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_13__ {scalar_t__ hIcon; int /*<<< orphan*/  hWnd; } ;
struct TYPE_12__ {TYPE_1__* hPrograms; int /*<<< orphan*/  hListView; TYPE_3__* hActiveProgram; } ;
struct TYPE_11__ {struct TYPE_11__* hWorkDir; struct TYPE_11__* hIconFile; struct TYPE_11__* hCmdLine; struct TYPE_11__* hName; struct TYPE_11__* Tags; TYPE_4__* hGroup; TYPE_2__* hPrior; TYPE_1__* hNext; int /*<<< orphan*/  iItem; } ;
struct TYPE_10__ {TYPE_1__* hNext; } ;
struct TYPE_9__ {TYPE_2__* hPrior; } ;
typedef  TYPE_3__ PROGRAM ;
typedef  TYPE_4__ PROGGROUP ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyIcon (scalar_t__) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_3__*) ; 
 int /*<<< orphan*/  GRPFILE_WriteGroupFile (TYPE_4__*) ; 
 int /*<<< orphan*/  LVM_DELETEITEM ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* program ; 

VOID PROGRAM_DeleteProgram(PROGRAM* hProgram, BOOL bUpdateGrpFile)
{
    PROGGROUP* group;

    group = hProgram->hGroup;
    if (hProgram->hGroup->hActiveProgram == hProgram)
        group->hActiveProgram = NULL;

    SendMessageA(group->hListView, LVM_DELETEITEM, hProgram->iItem, 0);

    if (hProgram->hPrior)
        hProgram->hPrior->hNext = hProgram->hNext;
    else
        hProgram->hGroup->hPrograms = hProgram->hNext;

    if (hProgram->hNext)
        hProgram->hNext->hPrior = hProgram->hPrior;

    if (bUpdateGrpFile)
        GRPFILE_WriteGroupFile(hProgram->hGroup);

#if 0
    DestroyWindow(program->hWnd);
    if (program->hIcon)
        DestroyIcon(program->hIcon);
#endif

    if (hProgram->Tags)
        Free(hProgram->Tags);
    Free(hProgram->hName);
    Free(hProgram->hCmdLine);
    Free(hProgram->hIconFile);
    Free(hProgram->hWorkDir);
    Free(hProgram);
}