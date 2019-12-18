#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  cid; int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;
struct TYPE_12__ {TYPE_1__* error; } ;
struct TYPE_11__ {int /*<<< orphan*/  error_no; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_2__* HPDF_MMgr ;
typedef  int /*<<< orphan*/  HPDF_List ;
typedef  TYPE_3__ HPDF_CidRange_Rec ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FreeMem (TYPE_2__*,TYPE_3__*) ; 
 TYPE_3__* HPDF_GetMem (TYPE_2__*,int) ; 
 int /*<<< orphan*/  HPDF_List_Add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  HPDF_OK ; 

__attribute__((used)) static HPDF_STATUS
AddCidRainge  (HPDF_MMgr            mmgr,
               HPDF_CidRange_Rec    range,
               HPDF_List            target)
{
    HPDF_CidRange_Rec *prange;
    HPDF_STATUS ret;

    prange = HPDF_GetMem (mmgr, sizeof(HPDF_CidRange_Rec));
    if (!prange)
        return mmgr->error->error_no;

    prange->from = range.from;
    prange->to = range.to;
    prange->cid = range.cid;

    if ((ret = HPDF_List_Add (target, prange))
                != HPDF_OK) {
        HPDF_FreeMem (mmgr, prange);
        return ret;
    }

    return HPDF_OK;
}