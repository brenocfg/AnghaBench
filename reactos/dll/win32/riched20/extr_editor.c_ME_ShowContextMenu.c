#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  cpMax; int /*<<< orphan*/  cpMin; } ;
struct TYPE_7__ {int /*<<< orphan*/  hwndParent; int /*<<< orphan*/  lpOleCallback; int /*<<< orphan*/  hWnd; } ;
typedef  TYPE_1__ ME_TextEditor ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  TYPE_2__ CHARRANGE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IRichEditOleCallback_GetContextMenu (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_GetSelectionOfs (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ME_GetSelectionType (TYPE_1__*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int TPM_LEFTALIGN ; 
 int TPM_RIGHTBUTTON ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TrackPopupMenu (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL ME_ShowContextMenu(ME_TextEditor *editor, int x, int y)
{
  CHARRANGE selrange;
  HMENU menu;
  int seltype;

  if(!editor->lpOleCallback || !editor->hWnd)
    return FALSE;
  ME_GetSelectionOfs(editor, &selrange.cpMin, &selrange.cpMax);
  seltype = ME_GetSelectionType(editor);
  if(SUCCEEDED(IRichEditOleCallback_GetContextMenu(editor->lpOleCallback, seltype, NULL, &selrange, &menu)))
  {
    TrackPopupMenu(menu, TPM_LEFTALIGN | TPM_RIGHTBUTTON, x, y, 0, editor->hwndParent, NULL);
    DestroyMenu(menu);
  }
  return TRUE;
}