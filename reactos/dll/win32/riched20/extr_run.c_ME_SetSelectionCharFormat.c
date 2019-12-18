#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* pBuffer; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pCharStyle; } ;
typedef  TYPE_2__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Style ;
typedef  int /*<<< orphan*/  ME_Cursor ;
typedef  int /*<<< orphan*/  CHARFORMAT2W ;

/* Variables and functions */
 int /*<<< orphan*/ * ME_ApplyStyle (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ME_GetInsertStyle (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_GetSelection (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ME_IsSelection (TYPE_2__*) ; 
 int /*<<< orphan*/  ME_ReleaseStyle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_SetCharFormat (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ME_SetSelectionCharFormat(ME_TextEditor *editor, CHARFORMAT2W *pFmt)
{
  if (!ME_IsSelection(editor))
  {
    ME_Style *s;
    if (!editor->pBuffer->pCharStyle)
      editor->pBuffer->pCharStyle = ME_GetInsertStyle(editor, 0);
    s = ME_ApplyStyle(editor, editor->pBuffer->pCharStyle, pFmt);
    ME_ReleaseStyle(editor->pBuffer->pCharStyle);
    editor->pBuffer->pCharStyle = s;
  } else {
    ME_Cursor *from, *to;
    ME_GetSelection(editor, &from, &to);
    ME_SetCharFormat(editor, from, to, pFmt);
  }
}