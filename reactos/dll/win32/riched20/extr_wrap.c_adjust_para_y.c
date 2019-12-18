#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_61__   TYPE_9__ ;
typedef  struct TYPE_60__   TYPE_8__ ;
typedef  struct TYPE_59__   TYPE_7__ ;
typedef  struct TYPE_58__   TYPE_6__ ;
typedef  struct TYPE_57__   TYPE_5__ ;
typedef  struct TYPE_56__   TYPE_4__ ;
typedef  struct TYPE_55__   TYPE_3__ ;
typedef  struct TYPE_54__   TYPE_2__ ;
typedef  struct TYPE_53__   TYPE_24__ ;
typedef  struct TYPE_52__   TYPE_23__ ;
typedef  struct TYPE_51__   TYPE_22__ ;
typedef  struct TYPE_50__   TYPE_21__ ;
typedef  struct TYPE_49__   TYPE_20__ ;
typedef  struct TYPE_48__   TYPE_1__ ;
typedef  struct TYPE_47__   TYPE_19__ ;
typedef  struct TYPE_46__   TYPE_18__ ;
typedef  struct TYPE_45__   TYPE_17__ ;
typedef  struct TYPE_44__   TYPE_16__ ;
typedef  struct TYPE_43__   TYPE_15__ ;
typedef  struct TYPE_42__   TYPE_14__ ;
typedef  struct TYPE_41__   TYPE_13__ ;
typedef  struct TYPE_40__   TYPE_12__ ;
typedef  struct TYPE_39__   TYPE_11__ ;
typedef  struct TYPE_38__   TYPE_10__ ;

/* Type definitions */
struct TYPE_60__ {int y; scalar_t__ x; } ;
struct TYPE_53__ {int nHeight; int yTextOffset; TYPE_8__ pt; TYPE_7__* next_cell; scalar_t__ nWidth; TYPE_4__* prev_cell; } ;
struct TYPE_61__ {TYPE_24__ cell; } ;
struct TYPE_41__ {int y; scalar_t__ x; } ;
struct TYPE_57__ {TYPE_13__ pt; } ;
struct TYPE_58__ {TYPE_5__ cell; } ;
struct TYPE_59__ {TYPE_6__ member; } ;
struct TYPE_54__ {int nHeight; } ;
struct TYPE_55__ {TYPE_2__ cell; } ;
struct TYPE_56__ {TYPE_3__ member; } ;
struct TYPE_52__ {TYPE_13__ pt; } ;
struct TYPE_48__ {scalar_t__ x; } ;
struct TYPE_40__ {int dxStartIndent; } ;
struct TYPE_45__ {int nFlags; int nHeight; TYPE_10__* pCell; TYPE_16__* next_para; TYPE_1__ pt; scalar_t__ nWidth; TYPE_12__ fmt; } ;
struct TYPE_46__ {int width; } ;
struct TYPE_39__ {int width; } ;
struct TYPE_47__ {TYPE_18__ bottom; TYPE_11__ top; } ;
struct TYPE_50__ {int yTextOffset; int nHeight; TYPE_22__* prev_cell; TYPE_13__ pt; TYPE_19__ border; scalar_t__ nWidth; TYPE_22__* next_cell; } ;
struct TYPE_49__ {TYPE_17__ para; TYPE_21__ cell; } ;
struct TYPE_51__ {TYPE_20__ member; } ;
struct TYPE_42__ {int nFlags; TYPE_10__* pCell; } ;
struct TYPE_43__ {TYPE_14__ para; } ;
struct TYPE_44__ {TYPE_15__ member; } ;
struct TYPE_38__ {TYPE_9__ member; } ;
typedef  TYPE_22__ ME_DisplayItem ;
typedef  TYPE_23__ ME_Context ;
typedef  TYPE_24__ ME_Cell ;

/* Variables and functions */
 int MEPF_ROWEND ; 
 int MEPF_ROWSTART ; 
 TYPE_22__* ME_FindItemBack (TYPE_22__*,int /*<<< orphan*/ ) ; 
 TYPE_22__* ME_FindItemFwd (TYPE_22__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_MarkRepaintEnd (TYPE_22__*,TYPE_22__**,TYPE_22__**) ; 
 scalar_t__ ME_twips2pointsX (TYPE_23__*,int) ; 
 int ME_twips2pointsY (TYPE_23__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  diCell ; 
 int /*<<< orphan*/  diParagraph ; 
 void* max (int,int) ; 

__attribute__((used)) static void adjust_para_y(ME_DisplayItem *item, ME_Context *c, ME_DisplayItem *repaint_start, ME_DisplayItem *repaint_end)
{
    if (item->member.para.nFlags & MEPF_ROWSTART)
    {
        ME_DisplayItem *cell = ME_FindItemFwd(item, diCell);
        ME_DisplayItem *endRowPara;
        int borderWidth = 0;
        cell->member.cell.pt = c->pt;
        /* Offset the text by the largest top border width. */
        while (cell->member.cell.next_cell)
        {
            borderWidth = max(borderWidth, cell->member.cell.border.top.width);
            cell = cell->member.cell.next_cell;
        }
        endRowPara = ME_FindItemFwd(cell, diParagraph);
        assert(endRowPara->member.para.nFlags & MEPF_ROWEND);
        if (borderWidth > 0)
        {
            borderWidth = max(ME_twips2pointsY(c, borderWidth), 1);
            while (cell)
            {
                cell->member.cell.yTextOffset = borderWidth;
                cell = cell->member.cell.prev_cell;
            }
            c->pt.y += borderWidth;
        }
        if (endRowPara->member.para.fmt.dxStartIndent > 0)
        {
            int dxStartIndent = endRowPara->member.para.fmt.dxStartIndent;
            cell = ME_FindItemFwd(item, diCell);
            cell->member.cell.pt.x += ME_twips2pointsX(c, dxStartIndent);
            c->pt.x = cell->member.cell.pt.x;
        }
    }
    else if (item->member.para.nFlags & MEPF_ROWEND)
    {
        /* Set all the cells to the height of the largest cell */
        ME_DisplayItem *startRowPara;
        int prevHeight, nHeight, bottomBorder = 0;
        ME_DisplayItem *cell = ME_FindItemBack(item, diCell);
        item->member.para.nWidth = cell->member.cell.pt.x + cell->member.cell.nWidth;
        if (!(item->member.para.next_para->member.para.nFlags & MEPF_ROWSTART))
        {
            /* Last row, the bottom border is added to the height. */
            cell = cell->member.cell.prev_cell;
            while (cell)
            {
                bottomBorder = max(bottomBorder, cell->member.cell.border.bottom.width);
                cell = cell->member.cell.prev_cell;
            }
            bottomBorder = ME_twips2pointsY(c, bottomBorder);
            cell = ME_FindItemBack(item, diCell);
        }
        prevHeight = cell->member.cell.nHeight;
        nHeight = cell->member.cell.prev_cell->member.cell.nHeight + bottomBorder;
        cell->member.cell.nHeight = nHeight;
        item->member.para.nHeight = nHeight;
        cell = cell->member.cell.prev_cell;
        cell->member.cell.nHeight = nHeight;
        while (cell->member.cell.prev_cell)
        {
            cell = cell->member.cell.prev_cell;
            cell->member.cell.nHeight = nHeight;
        }
        /* Also set the height of the start row paragraph */
        startRowPara = ME_FindItemBack(cell, diParagraph);
        startRowPara->member.para.nHeight = nHeight;
        c->pt.x = startRowPara->member.para.pt.x;
        c->pt.y = cell->member.cell.pt.y + nHeight;
        if (prevHeight < nHeight)
        {
            /* The height of the cells has grown, so invalidate the bottom of
             * the cells. */
            ME_MarkRepaintEnd(item, &repaint_start, &repaint_end);
            cell = ME_FindItemBack(item, diCell);
            while (cell)
            {
                ME_MarkRepaintEnd(ME_FindItemBack(cell, diParagraph), &repaint_start, &repaint_end);
                cell = cell->member.cell.prev_cell;
            }
        }
    }
    else if (item->member.para.pCell &&
             item->member.para.pCell != item->member.para.next_para->member.para.pCell)
    {
        /* The next paragraph is in the next cell in the table row. */
        ME_Cell *cell = &item->member.para.pCell->member.cell;
        cell->nHeight = c->pt.y + item->member.para.nHeight - cell->pt.y;

        /* Propagate the largest height to the end so that it can be easily
         * sent back to all the cells at the end of the row. */
        if (cell->prev_cell)
            cell->nHeight = max(cell->nHeight, cell->prev_cell->member.cell.nHeight);

        c->pt.x = cell->pt.x + cell->nWidth;
        c->pt.y = cell->pt.y;
        cell->next_cell->member.cell.pt = c->pt;
        if (!(item->member.para.next_para->member.para.nFlags & MEPF_ROWEND))
            c->pt.y += cell->yTextOffset;
    }
    else
    {
        if (item->member.para.pCell)
        {
            /* Next paragraph in the same cell. */
            c->pt.x = item->member.para.pCell->member.cell.pt.x;
        }
        else
            /* Normal paragraph */
            c->pt.x = 0;
        c->pt.y += item->member.para.nHeight;
    }
}