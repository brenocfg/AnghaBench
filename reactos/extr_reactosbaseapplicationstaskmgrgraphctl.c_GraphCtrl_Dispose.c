#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * m_brushBack; int /*<<< orphan*/ * m_dcPlot; int /*<<< orphan*/ * m_dcGrid; int /*<<< orphan*/ * m_bitmapPlot; int /*<<< orphan*/ * m_bitmapGrid; int /*<<< orphan*/ * m_bitmapOldPlot; int /*<<< orphan*/ * m_bitmapOldGrid; int /*<<< orphan*/ ** m_penPlot; } ;
typedef  TYPE_1__ TGraphCtrl ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int MAX_PLOTS ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void GraphCtrl_Dispose(TGraphCtrl* this)
{
    int plot;

    for (plot = 0; plot < MAX_PLOTS; plot++)
        DeleteObject(this->m_penPlot[plot]);

    /*  just to be picky restore the bitmaps for the two memory dc's */
    /*  (these dc's are being destroyed so there shouldn't be any leaks) */

    if (this->m_bitmapOldGrid != NULL) SelectObject(this->m_dcGrid, this->m_bitmapOldGrid);
    if (this->m_bitmapOldPlot != NULL) SelectObject(this->m_dcPlot, this->m_bitmapOldPlot);
    if (this->m_bitmapGrid    != NULL) DeleteObject(this->m_bitmapGrid);
    if (this->m_bitmapPlot    != NULL) DeleteObject(this->m_bitmapPlot);
    if (this->m_dcGrid        != NULL) DeleteDC(this->m_dcGrid);
    if (this->m_dcPlot        != NULL) DeleteDC(this->m_dcPlot);
    if (this->m_brushBack     != NULL) DeleteObject(this->m_brushBack);
}