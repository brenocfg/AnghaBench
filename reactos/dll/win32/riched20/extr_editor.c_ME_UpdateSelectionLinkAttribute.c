#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ nOffset; int /*<<< orphan*/  pRun; TYPE_4__* pPara; } ;
struct TYPE_13__ {int nCharOfs; TYPE_4__* next_para; TYPE_4__* prev_para; } ;
struct TYPE_14__ {TYPE_1__ para; } ;
struct TYPE_16__ {scalar_t__ type; TYPE_2__ member; } ;
struct TYPE_15__ {int /*<<< orphan*/  AutoURLDetect_bEnable; } ;
typedef  TYPE_3__ ME_TextEditor ;
typedef  TYPE_4__ ME_DisplayItem ;
typedef  TYPE_5__ ME_Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  ME_FindItemFwd (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_GetSelection (TYPE_3__*,TYPE_5__**,TYPE_5__**) ; 
 int /*<<< orphan*/  ME_UpdateLinkAttribute (TYPE_3__*,TYPE_5__*,int) ; 
 scalar_t__ diParagraph ; 
 int /*<<< orphan*/  diRun ; 

__attribute__((used)) static void ME_UpdateSelectionLinkAttribute(ME_TextEditor *editor)
{
  ME_DisplayItem *startPara, *endPara;
  ME_DisplayItem *prev_para;
  ME_Cursor *from, *to;
  ME_Cursor start;
  int nChars;

  if (!editor->AutoURLDetect_bEnable) return;

  ME_GetSelection(editor, &from, &to);

  /* Find paragraph previous to the one that contains start cursor */
  startPara = from->pPara;
  prev_para = startPara->member.para.prev_para;
  if (prev_para->type == diParagraph) startPara = prev_para;

  /* Find paragraph that contains end cursor */
  endPara = to->pPara->member.para.next_para;

  start.pPara = startPara;
  start.pRun = ME_FindItemFwd(startPara, diRun);
  start.nOffset = 0;
  nChars = endPara->member.para.nCharOfs - startPara->member.para.nCharOfs;

  ME_UpdateLinkAttribute(editor, &start, nChars);
}