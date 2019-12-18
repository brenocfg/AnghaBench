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
struct TYPE_3__ {int stemv; int italic_angle; int /*<<< orphan*/  flags; int /*<<< orphan*/  attr; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_FontDef ;
typedef  scalar_t__ HPDF_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FONT_FOURCE_BOLD ; 
 int /*<<< orphan*/  HPDF_FONT_ITALIC ; 
 int /*<<< orphan*/  HPDF_INVALID_FONTDEF_DATA ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_STATUS
HPDF_CIDFontDef_ChangeStyle  (HPDF_FontDef   fontdef,
                              HPDF_BOOL      bold,
                              HPDF_BOOL      italic)
{
    HPDF_PTRACE ((" HPDF_CIDFontDef_ChangeStyle\n"));

    if (!fontdef || !fontdef->attr)
        return HPDF_INVALID_FONTDEF_DATA;

    if (bold) {
        fontdef->stemv *= 2;
        fontdef->flags |= HPDF_FONT_FOURCE_BOLD;
    }

    if (italic) {
        fontdef->italic_angle -= 11;
        fontdef->flags |= HPDF_FONT_ITALIC;
    }

    return HPDF_OK;
}