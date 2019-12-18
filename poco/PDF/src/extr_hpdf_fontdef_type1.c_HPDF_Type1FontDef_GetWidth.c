#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ unicode; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {int /*<<< orphan*/  missing_width; int /*<<< orphan*/  attr; } ;
struct TYPE_5__ {scalar_t__ widths_count; TYPE_3__* widths; } ;
typedef  scalar_t__ HPDF_UNICODE ;
typedef  scalar_t__ HPDF_UINT ;
typedef  TYPE_1__* HPDF_Type1FontDefAttr ;
typedef  int /*<<< orphan*/  HPDF_INT16 ;
typedef  TYPE_2__* HPDF_FontDef ;
typedef  TYPE_3__ HPDF_CharData ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_INT16
HPDF_Type1FontDef_GetWidth  (HPDF_FontDef  fontdef,
                             HPDF_UNICODE  unicode)
{
    HPDF_Type1FontDefAttr attr = (HPDF_Type1FontDefAttr)fontdef->attr;
    HPDF_CharData *cdata = attr->widths;
    HPDF_UINT i;

    HPDF_PTRACE ((" HPDF_Type1FontDef_GetWidth\n"));

    for (i = 0; i < attr->widths_count; i++) {
        if (cdata->unicode == unicode)
            return cdata->width;
        cdata++;
    }

    return fontdef->missing_width;
}