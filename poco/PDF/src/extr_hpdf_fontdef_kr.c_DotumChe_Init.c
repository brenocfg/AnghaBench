#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ascent; int descent; int cap_height; int stemv; int /*<<< orphan*/  valid; int /*<<< orphan*/  type; scalar_t__ italic_angle; scalar_t__ flags; int /*<<< orphan*/  font_bbox; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_FontDef ;

/* Variables and functions */
 int /*<<< orphan*/  DotumChe_W_ARRAY ; 
 int /*<<< orphan*/  HPDF_CIDFontDef_AddWidth (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FONTDEF_TYPE_CID ; 
 scalar_t__ HPDF_FONT_FIXED_WIDTH ; 
 scalar_t__ HPDF_FONT_SYMBOLIC ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_TRUE ; 
 int /*<<< orphan*/  HPDF_ToBox (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static HPDF_STATUS
DotumChe_Init  (HPDF_FontDef   fontdef)
{
    HPDF_STATUS ret;

    HPDF_PTRACE ((" HPDF_FontDef_DotumChe_Init\n"));

    fontdef->ascent = 858;
    fontdef->descent = -141;
    fontdef->cap_height = 679;
    fontdef->font_bbox = HPDF_ToBox(0, -150, 1000, 863);
    fontdef->flags = HPDF_FONT_SYMBOLIC + HPDF_FONT_FIXED_WIDTH;
    fontdef->italic_angle = 0;
    fontdef->stemv = 78;
    if ((ret = HPDF_CIDFontDef_AddWidth (fontdef, DotumChe_W_ARRAY)) !=
                HPDF_OK) {
        return ret;
    }

    fontdef->type = HPDF_FONTDEF_TYPE_CID;
    fontdef->valid = HPDF_TRUE;

    return HPDF_OK;
}