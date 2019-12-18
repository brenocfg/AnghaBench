#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int nCharOfs; } ;
struct TYPE_11__ {int nCharOfs; TYPE_6__* next_para; scalar_t__ nRows; } ;
struct TYPE_13__ {TYPE_3__ run; TYPE_2__ para; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_4__ member; } ;
struct TYPE_14__ {TYPE_1__* pBuffer; } ;
struct TYPE_10__ {TYPE_6__* pFirst; } ;
typedef  TYPE_5__ ME_TextEditor ;
typedef  TYPE_6__ ME_DisplayItem ;

/* Variables and functions */
 TYPE_6__* ME_FindItemFwd (TYPE_6__*,scalar_t__) ; 
 scalar_t__ diParagraph ; 
 scalar_t__ diRun ; 
 scalar_t__ diStartRowOrParagraph ; 

int
ME_RowNumberFromCharOfs(ME_TextEditor *editor, int nOfs)
{
  ME_DisplayItem *item = ME_FindItemFwd(editor->pBuffer->pFirst, diParagraph);
  int nRow = 0;

  while (item->type == diParagraph &&
         item->member.para.next_para->member.para.nCharOfs <= nOfs)
  {
    nRow += item->member.para.nRows;
    item = item->member.para.next_para;
  }
  if (item->type == diParagraph)
  {
    ME_DisplayItem *next_para = item->member.para.next_para;

    nOfs -= item->member.para.nCharOfs;
    item = ME_FindItemFwd(item, diRun);
    while ((item = ME_FindItemFwd(item, diStartRowOrParagraph)) != NULL)
    {
      if (item == next_para)
        break;
      item = ME_FindItemFwd(item, diRun);
      if (item->member.run.nCharOfs > nOfs)
        break;
      nRow++;
    }
  }
  return nRow;
}