#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int missing_width; int DW; int* DW2; TYPE_1__* mmgr; int /*<<< orphan*/  widths; struct TYPE_14__* attr; int /*<<< orphan*/  valid; int /*<<< orphan*/  init_fn; int /*<<< orphan*/  free_fn; int /*<<< orphan*/  type; int /*<<< orphan*/  error; scalar_t__ base_font; int /*<<< orphan*/  sig_bytes; } ;
struct TYPE_13__ {int /*<<< orphan*/  error; } ;
typedef  TYPE_1__* HPDF_MMgr ;
typedef  int /*<<< orphan*/  HPDF_FontDef_Rec ;
typedef  int /*<<< orphan*/  HPDF_FontDef_InitFunc ;
typedef  TYPE_2__* HPDF_FontDef ;
typedef  int /*<<< orphan*/  HPDF_CIDFontDefAttr_Rec ;
typedef  TYPE_2__* HPDF_CIDFontDefAttr ;
typedef  TYPE_2__ HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_CIDFontDef_FreeFunc ; 
 int /*<<< orphan*/  HPDF_DEF_CHAR_WIDTHS_NUM ; 
 int /*<<< orphan*/  HPDF_FALSE ; 
 int /*<<< orphan*/  HPDF_FONTDEF_SIG_BYTES ; 
 int /*<<< orphan*/  HPDF_FONTDEF_TYPE_UNINITIALIZED ; 
 int /*<<< orphan*/  HPDF_FreeMem (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* HPDF_GetMem (TYPE_1__*,int) ; 
 scalar_t__ HPDF_LIMIT_MAX_NAME_LEN ; 
 int /*<<< orphan*/  HPDF_List_New (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_StrCpy (scalar_t__,char*,scalar_t__) ; 

HPDF_FontDef
HPDF_CIDFontDef_New  (HPDF_MMgr               mmgr,
                      char              *name,
                      HPDF_FontDef_InitFunc   init_fn)
{
    HPDF_FontDef fontdef;
    HPDF_CIDFontDefAttr fontdef_attr;

    HPDF_PTRACE ((" HPDF_CIDFontDef_New\n"));

    if (!mmgr)
        return NULL;

    fontdef = HPDF_GetMem (mmgr, sizeof(HPDF_FontDef_Rec));
    if (!fontdef)
        return NULL;

    HPDF_MemSet (fontdef, 0, sizeof(HPDF_FontDef_Rec));
    fontdef->sig_bytes = HPDF_FONTDEF_SIG_BYTES;
    HPDF_StrCpy (fontdef->base_font, name, fontdef->base_font +
                    HPDF_LIMIT_MAX_NAME_LEN);
    fontdef->mmgr = mmgr;
    fontdef->error = mmgr->error;
    fontdef->type = HPDF_FONTDEF_TYPE_UNINITIALIZED;
    fontdef->free_fn = HPDF_CIDFontDef_FreeFunc;
    fontdef->init_fn = init_fn;
    fontdef->valid = HPDF_FALSE;
    fontdef_attr = HPDF_GetMem (mmgr, sizeof(HPDF_CIDFontDefAttr_Rec));
    if (!fontdef_attr) {
        HPDF_FreeMem (fontdef->mmgr, fontdef);
        return NULL;
    }

    fontdef->attr = fontdef_attr;
    HPDF_MemSet ((HPDF_BYTE *)fontdef_attr, 0,
                sizeof(HPDF_CIDFontDefAttr_Rec));

    fontdef_attr->widths = HPDF_List_New (mmgr, HPDF_DEF_CHAR_WIDTHS_NUM);
    if (!fontdef_attr->widths) {
        HPDF_FreeMem (fontdef->mmgr, fontdef);
        HPDF_FreeMem (fontdef->mmgr, fontdef_attr);
        return NULL;
    }

    fontdef->missing_width = 500;
    fontdef_attr->DW = 1000;
    fontdef_attr->DW2[0] = 880;
    fontdef_attr->DW2[1] = -1000;

    return fontdef;
}