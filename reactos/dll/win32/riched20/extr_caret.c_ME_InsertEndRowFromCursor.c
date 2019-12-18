#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Style ;

/* Variables and functions */
 int /*<<< orphan*/  MERF_ENDROW ; 
 int /*<<< orphan*/  ME_DeleteSelection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ME_GetInsertStyle (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ME_InternalInsertTextFromCursor (int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ME_IsSelection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_ReleaseStyle (int /*<<< orphan*/ *) ; 

void ME_InsertEndRowFromCursor(ME_TextEditor *editor, int nCursor)
{
  ME_Style              *pStyle = ME_GetInsertStyle(editor, nCursor);
  WCHAR                 space = ' ';

  /* FIXME no no no */
  if (ME_IsSelection(editor))
    ME_DeleteSelection(editor);

  ME_InternalInsertTextFromCursor(editor, nCursor, &space, 1, pStyle,
                                  MERF_ENDROW);
  ME_ReleaseStyle(pStyle);
}