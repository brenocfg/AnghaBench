#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* pBuffer; } ;
struct TYPE_9__ {TYPE_1__* pCharStyle; } ;
struct TYPE_8__ {int /*<<< orphan*/  fmt; } ;
typedef  TYPE_3__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Cursor ;
typedef  int /*<<< orphan*/  CHARFORMAT2W ;

/* Variables and functions */
 int /*<<< orphan*/  ME_CopyCharFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_GetCharFormat (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_GetSelection (TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ME_IsSelection (TYPE_3__*) ; 

void ME_GetSelectionCharFormat(ME_TextEditor *editor, CHARFORMAT2W *pFmt)
{
  ME_Cursor *from, *to;
  if (!ME_IsSelection(editor) && editor->pBuffer->pCharStyle)
  {
    ME_CopyCharFormat(pFmt, &editor->pBuffer->pCharStyle->fmt);
    return;
  }
  ME_GetSelection(editor, &from, &to);
  ME_GetCharFormat(editor, from, to, pFmt);
}