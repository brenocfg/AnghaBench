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
typedef  int /*<<< orphan*/  HPDF_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FontDef_Free (int /*<<< orphan*/ *) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_Stream_Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HPDF_TTFontDef_New (int /*<<< orphan*/ ) ; 
 scalar_t__ LoadFontData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_FontDef
HPDF_TTFontDef_Load  (HPDF_MMgr     mmgr,
                      HPDF_Stream   stream,
                      HPDF_BOOL     embedding)
{
    HPDF_STATUS ret;
    HPDF_FontDef fontdef;

    HPDF_PTRACE ((" HPDF_TTFontDef_Load\n"));

    fontdef = HPDF_TTFontDef_New (mmgr);

    if (!fontdef) {
        HPDF_Stream_Free (stream);
        return NULL;
    }

    ret = LoadFontData (fontdef, stream, embedding, 0);
    if (ret != HPDF_OK) {
        HPDF_FontDef_Free (fontdef);
        return NULL;
    }

    return fontdef;
}