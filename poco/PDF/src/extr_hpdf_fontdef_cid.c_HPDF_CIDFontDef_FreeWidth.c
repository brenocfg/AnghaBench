#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ count; } ;
struct TYPE_7__ {TYPE_3__* widths; } ;
struct TYPE_6__ {int /*<<< orphan*/  valid; int /*<<< orphan*/  mmgr; int /*<<< orphan*/  attr; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  TYPE_1__* HPDF_FontDef ;
typedef  int /*<<< orphan*/  HPDF_CID_Width ;
typedef  TYPE_2__* HPDF_CIDFontDefAttr ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FALSE ; 
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_List_Free (TYPE_3__*) ; 
 scalar_t__ HPDF_List_ItemAt (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

void
HPDF_CIDFontDef_FreeWidth  (HPDF_FontDef  fontdef)
{
    HPDF_CIDFontDefAttr attr = (HPDF_CIDFontDefAttr)fontdef->attr;
    HPDF_UINT i;

    HPDF_PTRACE ((" HPDF_FontDef_Validate\n"));

    for (i = 0; i < attr->widths->count; i++) {
        HPDF_CID_Width *w =
                    (HPDF_CID_Width *)HPDF_List_ItemAt (attr->widths, i);

        HPDF_FreeMem (fontdef->mmgr, w);
    }

    HPDF_List_Free (attr->widths);
    attr->widths = NULL;

    fontdef->valid = HPDF_FALSE;
}