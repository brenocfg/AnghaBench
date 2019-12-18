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
struct TYPE_7__ {int /*<<< orphan*/  attr; } ;
struct TYPE_5__ {int* flgs; } ;
struct TYPE_6__ {int num_glyphs; TYPE_1__ glyph_tbl; } ;
typedef  TYPE_2__* HPDF_TTFontDefAttr ;
typedef  TYPE_3__* HPDF_FontDef ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_MemSet (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
CleanFunc (HPDF_FontDef   fontdef)
{
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;
    HPDF_MemSet (attr->glyph_tbl.flgs, 0,
            sizeof (HPDF_BYTE) * attr->num_glyphs);
    attr->glyph_tbl.flgs[0] = 1;
}