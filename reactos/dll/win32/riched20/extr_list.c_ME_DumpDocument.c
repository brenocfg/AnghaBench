#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  nFlags; int /*<<< orphan*/  nCharOfs; } ;
struct TYPE_9__ {int nFlags; int /*<<< orphan*/  nCharOfs; } ;
struct TYPE_8__ {int /*<<< orphan*/  prev_cell; int /*<<< orphan*/  next_cell; int /*<<< orphan*/  nNestingLevel; } ;
struct TYPE_10__ {TYPE_2__ para; TYPE_6__ run; TYPE_1__ cell; } ;
struct TYPE_12__ {int type; struct TYPE_12__* next; TYPE_3__ member; } ;
struct TYPE_11__ {TYPE_5__* pFirst; } ;
typedef  TYPE_4__ ME_TextBuffer ;
typedef  TYPE_5__ ME_DisplayItem ;

/* Variables and functions */
 int MEPF_ROWEND ; 
 int MEPF_ROWSTART ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debugstr_run (TYPE_6__*) ; 
#define  diCell 133 
#define  diParagraph 132 
#define  diRun 131 
#define  diStartRow 130 
#define  diTextEnd 129 
#define  diTextStart 128 

void ME_DumpDocument(ME_TextBuffer *buffer)
{
  /* FIXME this is useless, */
  ME_DisplayItem *pItem = buffer->pFirst;
  TRACE("DOCUMENT DUMP START\n");
  while(pItem) {
    switch(pItem->type)
    {
      case diTextStart:
        TRACE("Start\n");
        break;
      case diCell:
        TRACE("Cell(level=%d%s)\n", pItem->member.cell.nNestingLevel,
              !pItem->member.cell.next_cell ? ", END" :
                (!pItem->member.cell.prev_cell ? ", START" :""));
        break;
      case diParagraph:
        TRACE("Paragraph(ofs=%d)\n", pItem->member.para.nCharOfs);
        if (pItem->member.para.nFlags & MEPF_ROWSTART)
          TRACE(" - (Table Row Start)\n");
        if (pItem->member.para.nFlags & MEPF_ROWEND)
          TRACE(" - (Table Row End)\n");
        break;
      case diStartRow:
        TRACE(" - StartRow\n");
        break;
      case diRun:
        TRACE(" - Run(%s, %d, flags=%x)\n", debugstr_run( &pItem->member.run ),
          pItem->member.run.nCharOfs, pItem->member.run.nFlags);
        break;
      case diTextEnd:
        TRACE("End(ofs=%d)\n", pItem->member.para.nCharOfs);
        break;
      default:
        break;
    }
    pItem = pItem->next;
  }
  TRACE("DOCUMENT DUMP END\n");
}