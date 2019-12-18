#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_29__ {int /*<<< orphan*/  text; scalar_t__ nCharOfs; } ;
struct TYPE_28__ {scalar_t__ nOffset; TYPE_5__* pRun; } ;
struct TYPE_23__ {scalar_t__ len; TYPE_8__* para; scalar_t__ nCharOfs; } ;
struct TYPE_24__ {TYPE_1__ run; } ;
struct TYPE_27__ {TYPE_2__ member; } ;
struct TYPE_26__ {int nCursors; TYPE_3__* pCursors; } ;
struct TYPE_25__ {int nOffset; TYPE_5__* pRun; } ;
typedef  TYPE_4__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Style ;
typedef  TYPE_5__ ME_DisplayItem ;
typedef  TYPE_6__ ME_Cursor ;

/* Variables and functions */
 TYPE_5__* ME_FindItemBack (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ME_FindItemFwd (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_InsertBefore (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ME_InsertString (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*,int) ; 
 TYPE_5__* ME_MakeRun (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ME_PropagateCharOffset (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ME_SplitRunSimple (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  add_undo_delete_run (TYPE_4__*,scalar_t__,int) ; 
 int /*<<< orphan*/  diRun ; 
 int /*<<< orphan*/  get_di_from_para (TYPE_8__*) ; 
 int /*<<< orphan*/  mark_para_rewrap (TYPE_4__*,int /*<<< orphan*/ ) ; 

ME_DisplayItem *
ME_InsertRunAtCursor(ME_TextEditor *editor, ME_Cursor *cursor, ME_Style *style,
                     const WCHAR *str, int len, int flags)
{
  ME_DisplayItem *pDI, *insert_before = cursor->pRun, *prev;

  if (cursor->nOffset)
  {
    if (cursor->nOffset == cursor->pRun->member.run.len)
    {
      insert_before = ME_FindItemFwd( cursor->pRun, diRun );
      if (!insert_before) insert_before = cursor->pRun; /* Always insert before the final eop run */
    }
    else
    {
      ME_SplitRunSimple( editor, cursor );
      insert_before = cursor->pRun;
    }
  }

  add_undo_delete_run( editor, insert_before->member.run.para->nCharOfs +
                       insert_before->member.run.nCharOfs, len );

  pDI = ME_MakeRun(style, flags);
  pDI->member.run.nCharOfs = insert_before->member.run.nCharOfs;
  pDI->member.run.len = len;
  pDI->member.run.para = insert_before->member.run.para;
  ME_InsertString( pDI->member.run.para->text, pDI->member.run.nCharOfs, str, len );
  ME_InsertBefore( insert_before, pDI );
  TRACE("Shift length:%d\n", len);
  ME_PropagateCharOffset( insert_before, len );
  mark_para_rewrap(editor, get_di_from_para(insert_before->member.run.para));

  /* Move any cursors that were at the end of the previous run to the end of the inserted run */
  prev = ME_FindItemBack( pDI, diRun );
  if (prev)
  {
    int i;

    for (i = 0; i < editor->nCursors; i++)
    {
      if (editor->pCursors[i].pRun == prev &&
          editor->pCursors[i].nOffset == prev->member.run.len)
      {
        editor->pCursors[i].pRun = pDI;
        editor->pCursors[i].nOffset = len;
      }
    }
  }

  return pDI;
}