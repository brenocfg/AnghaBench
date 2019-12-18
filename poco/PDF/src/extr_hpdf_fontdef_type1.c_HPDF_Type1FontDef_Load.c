#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;
typedef  int /*<<< orphan*/ * HPDF_FontDef ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FontDef_Free (int /*<<< orphan*/ *) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/ * HPDF_Type1FontDef_New (int /*<<< orphan*/ ) ; 
 scalar_t__ LoadAfm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ LoadFontData (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

HPDF_FontDef
HPDF_Type1FontDef_Load  (HPDF_MMgr         mmgr,
                         HPDF_Stream       afm,
                         HPDF_Stream       font_data)
{
    HPDF_FontDef fontdef;
    HPDF_STATUS ret;

    HPDF_PTRACE ((" HPDF_Type1FontDef_Load\n"));

    if (!afm)
        return NULL;

    fontdef = HPDF_Type1FontDef_New (mmgr);

    if (!fontdef)
        return NULL;

    ret = LoadAfm (fontdef, afm);
    if (ret != HPDF_OK) {
        HPDF_FontDef_Free (fontdef);
        return NULL;
    }

    /* if font-data is specified, the font data is embeded */
    if (font_data) {
        ret = LoadFontData (fontdef, font_data);
        if (ret != HPDF_OK) {
            HPDF_FontDef_Free (fontdef);
            return NULL;
        }
    }

    return fontdef;
}