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
struct TYPE_4__ {int /*<<< orphan*/  mmgr; int /*<<< orphan*/  attr; } ;
typedef  TYPE_1__* HPDF_FontDef ;
typedef  int /*<<< orphan*/  HPDF_CIDFontDefAttr ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_CIDFontDef_FreeWidth (TYPE_1__*) ; 
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

void
HPDF_CIDFontDef_FreeFunc (HPDF_FontDef  fontdef)
{
    HPDF_CIDFontDefAttr attr = (HPDF_CIDFontDefAttr)fontdef->attr;

    HPDF_PTRACE ((" HPDF_CIDFontDef_FreeFunc\n"));

    HPDF_CIDFontDef_FreeWidth (fontdef);
    HPDF_FreeMem (fontdef->mmgr, attr);
}