#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {int /*<<< orphan*/  hEdit; } ;
typedef  int /*<<< orphan*/  FINDREPLACE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EM_SETSEL ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__ Globals ; 
 scalar_t__ NOTEPAD_FindNext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static VOID NOTEPAD_ReplaceAll(FINDREPLACE *pFindReplace)
{
    BOOL bShowAlert = TRUE;

    SendMessage(Globals.hEdit, EM_SETSEL, 0, 0);

    while (NOTEPAD_FindNext(pFindReplace, TRUE, bShowAlert))
    {
        bShowAlert = FALSE;
    }
}