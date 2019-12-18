#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_22__ ;
typedef  struct TYPE_36__   TYPE_20__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_19__ ;
typedef  struct TYPE_33__   TYPE_18__ ;
typedef  struct TYPE_32__   TYPE_17__ ;
typedef  struct TYPE_31__   TYPE_16__ ;
typedef  struct TYPE_30__   TYPE_15__ ;
typedef  struct TYPE_29__   TYPE_14__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
struct TYPE_45__ {int dxStartIndent; } ;
struct TYPE_42__ {scalar_t__ nRightBoundary; } ;
struct TYPE_43__ {TYPE_6__ cell; } ;
struct TYPE_44__ {TYPE_7__ member; } ;
struct TYPE_30__ {int dwMask; int wEffects; } ;
struct TYPE_40__ {int nFlags; TYPE_3__* pCell; TYPE_15__ fmt; } ;
struct TYPE_41__ {TYPE_4__ para; } ;
struct TYPE_33__ {int nRightBoundary; scalar_t__ nWidth; TYPE_8__* prev_cell; } ;
struct TYPE_38__ {TYPE_18__ cell; } ;
struct TYPE_39__ {TYPE_2__ member; } ;
struct TYPE_35__ {TYPE_18__ cell; } ;
struct TYPE_37__ {TYPE_1__ member; } ;
struct TYPE_25__ {TYPE_9__ fmt; } ;
struct TYPE_26__ {TYPE_10__ para; } ;
struct TYPE_36__ {TYPE_11__ member; } ;
struct TYPE_27__ {int /*<<< orphan*/  x; } ;
struct TYPE_34__ {TYPE_13__* editor; TYPE_12__ pt; scalar_t__ nAvailWidth; } ;
struct TYPE_32__ {TYPE_5__ member; } ;
struct TYPE_29__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_31__ {TYPE_14__ pt; TYPE_19__* context; scalar_t__ nRightMargin; scalar_t__ nFirstMargin; scalar_t__ nLeftMargin; scalar_t__ nRow; scalar_t__ nAvailWidth; void* bWordWrap; int /*<<< orphan*/ * pLastSplittableRun; void* bOverflown; int /*<<< orphan*/ * pRowStart; TYPE_17__* pPara; } ;
struct TYPE_28__ {scalar_t__ bEmulateVersion10; void* bWordWrap; } ;
typedef  TYPE_15__ PARAFORMAT2 ;
typedef  TYPE_16__ ME_WrapContext ;
typedef  TYPE_17__ ME_DisplayItem ;
typedef  TYPE_18__ ME_Cell ;

/* Variables and functions */
 void* FALSE ; 
 int MEPF_ROWEND ; 
 int MEPF_ROWSTART ; 
 TYPE_22__* ME_FindItemBack (TYPE_17__*,int /*<<< orphan*/ ) ; 
 TYPE_20__* ME_GetTableRowEnd (TYPE_17__*) ; 
 int /*<<< orphan*/  ME_twips2pointsX (TYPE_19__*,int) ; 
 int PFE_TABLE ; 
 int PFM_TABLE ; 
 void* TRUE ; 
 int /*<<< orphan*/  diCell ; 
 scalar_t__ max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ME_BeginRow(ME_WrapContext *wc)
{
  PARAFORMAT2 *pFmt;
  ME_DisplayItem *para = wc->pPara;

  pFmt = &para->member.para.fmt;
  wc->pRowStart = NULL;
  wc->bOverflown = FALSE;
  wc->pLastSplittableRun = NULL;
  wc->bWordWrap = wc->context->editor->bWordWrap;
  if (para->member.para.nFlags & (MEPF_ROWSTART|MEPF_ROWEND)) {
    wc->nAvailWidth = 0;
    wc->bWordWrap = FALSE;
    if (para->member.para.nFlags & MEPF_ROWEND)
    {
      ME_Cell *cell = &ME_FindItemBack(para, diCell)->member.cell;
      cell->nWidth = 0;
    }
  } else if (para->member.para.pCell) {
    ME_Cell *cell = &para->member.para.pCell->member.cell;
    int width;

    width = cell->nRightBoundary;
    if (cell->prev_cell)
      width -= cell->prev_cell->member.cell.nRightBoundary;
    if (!cell->prev_cell)
    {
      int rowIndent = ME_GetTableRowEnd(para)->member.para.fmt.dxStartIndent;
      width -= rowIndent;
    }
    cell->nWidth = max(ME_twips2pointsX(wc->context, width), 0);

    wc->nAvailWidth = cell->nWidth
        - (wc->nRow ? wc->nLeftMargin : wc->nFirstMargin) - wc->nRightMargin;
    wc->bWordWrap = TRUE;
  } else {
    wc->nAvailWidth = wc->context->nAvailWidth
        - (wc->nRow ? wc->nLeftMargin : wc->nFirstMargin) - wc->nRightMargin;
  }
  wc->pt.x = wc->context->pt.x;
  if (wc->context->editor->bEmulateVersion10 && /* v1.0 - 3.0 */
      pFmt->dwMask & PFM_TABLE && pFmt->wEffects & PFE_TABLE)
    /* Shift the text down because of the border. */
    wc->pt.y++;
}