#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int unicode; int /*<<< orphan*/  width; int /*<<< orphan*/  char_cd; } ;
struct TYPE_9__ {int /*<<< orphan*/  missing_width; int /*<<< orphan*/  error; int /*<<< orphan*/  mmgr; int /*<<< orphan*/  attr; } ;
struct TYPE_8__ {int widths_count; TYPE_3__* widths; } ;
typedef  int HPDF_UINT ;
typedef  TYPE_1__* HPDF_Type1FontDefAttr ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_2__* HPDF_FontDef ;
typedef  TYPE_3__ HPDF_CharData ;

/* Variables and functions */
 int /*<<< orphan*/  FreeWidth (TYPE_2__*) ; 
 int /*<<< orphan*/  HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_GetMem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_MemSet (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_STATUS
HPDF_Type1FontDef_SetWidths  (HPDF_FontDef          fontdef,
                              const HPDF_CharData*  widths)
{
    const HPDF_CharData* src = widths;
    HPDF_Type1FontDefAttr attr = (HPDF_Type1FontDefAttr)fontdef->attr;
    HPDF_CharData* dst;
    HPDF_UINT i = 0;

    HPDF_PTRACE ((" HPDF_Type1FontDef_SetWidths\n"));

    FreeWidth (fontdef);

    while (src->unicode != 0xFFFF) {
        src++;
        i++;
    }

    attr->widths_count = i;

    dst = (HPDF_CharData*)HPDF_GetMem (fontdef->mmgr, sizeof(HPDF_CharData) *
            attr->widths_count);
    if (dst == NULL)
        return HPDF_Error_GetCode (fontdef->error);

    HPDF_MemSet (dst, 0, sizeof(HPDF_CharData) * attr->widths_count);
    attr->widths = dst;

    src = widths;
    for (i = 0; i < attr->widths_count; i++) {
        dst->char_cd = src->char_cd;
        dst->unicode = src->unicode;
        dst->width = src->width;
        if (dst->unicode == 0x0020) {
            fontdef->missing_width = src->width;
        }

        src++;
        dst++;
    }

    return HPDF_OK;
}