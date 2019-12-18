#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {int /*<<< orphan*/  hMainWnd; scalar_t__ bMinOnRun; } ;
struct TYPE_4__ {int /*<<< orphan*/  nCmdShow; int /*<<< orphan*/  hWorkDir; int /*<<< orphan*/  hCmdLine; } ;
typedef  TYPE_1__ PROGRAM ;

/* Variables and functions */
 int /*<<< orphan*/  CloseWindow (int /*<<< orphan*/ ) ; 
 TYPE_3__ Globals ; 
 int /*<<< orphan*/  ShellExecuteW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID PROGRAM_ExecuteProgram(PROGRAM* hProgram)
{
    // TODO: Use a (private?) shell API with which one can use hProgram->bNewVDM

    ShellExecuteW(NULL, NULL, hProgram->hCmdLine, NULL, hProgram->hWorkDir, hProgram->nCmdShow);

    if (Globals.bMinOnRun)
        CloseWindow(Globals.hMainWnd);
}