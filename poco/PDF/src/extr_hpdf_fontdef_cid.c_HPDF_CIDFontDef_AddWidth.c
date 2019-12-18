#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  widths; } ;
struct TYPE_12__ {int cid; int /*<<< orphan*/  width; } ;
struct TYPE_11__ {int /*<<< orphan*/  mmgr; TYPE_1__* error; int /*<<< orphan*/  attr; } ;
struct TYPE_10__ {int /*<<< orphan*/  error_no; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_2__* HPDF_FontDef ;
typedef  TYPE_3__ HPDF_CID_Width ;
typedef  TYPE_4__* HPDF_CIDFontDefAttr ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* HPDF_GetMem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_List_Add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_STATUS
HPDF_CIDFontDef_AddWidth  (HPDF_FontDef            fontdef,
                           const HPDF_CID_Width   *widths)
{
    HPDF_CIDFontDefAttr attr = (HPDF_CIDFontDefAttr)fontdef->attr;

    HPDF_PTRACE ((" HPDF_CIDFontDef_AddWidth\n"));

    while (widths->cid != 0xFFFF) {
        HPDF_CID_Width *w = HPDF_GetMem (fontdef->mmgr,
                sizeof (HPDF_CID_Width));
        HPDF_STATUS ret;

        if (!w)
            return fontdef->error->error_no;

        w->cid = widths->cid;
        w->width = widths->width;

        if ((ret = HPDF_List_Add (attr->widths, w)) != HPDF_OK) {
            HPDF_FreeMem (fontdef->mmgr, w);

            return ret;
        }

        widths++;
    }

    return HPDF_OK;
}