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
struct TYPE_4__ {int nCursors; int nModifyStep; int /*<<< orphan*/ * pCursors; } ;
typedef  TYPE_1__ ME_TextEditor ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ME_InternalDeleteText (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

BOOL ME_DeleteTextAtCursor(ME_TextEditor *editor, int nCursor, int nChars)
{
  assert(nCursor>=0 && nCursor<editor->nCursors);
  /* text operations set modified state */
  editor->nModifyStep = 1;
  return ME_InternalDeleteText(editor, &editor->pCursors[nCursor],
                               nChars, FALSE);
}